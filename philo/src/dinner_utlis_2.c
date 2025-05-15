/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utlis_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:46:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/15 08:30:47 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	acquire_forks(t_philo *philo)
{
	if (philo->left_fork->id < philo->right_fork->id)
	{
		pthread_mutex_lock(&(philo->left_fork->fork));
		print_status(philo, FORK);
		pthread_mutex_lock(&(philo->right_fork->fork));
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&(philo->right_fork->fork));
		print_status(philo, FORK);
		pthread_mutex_lock(&(philo->left_fork->fork));
		print_status(philo, FORK);
	}
}

int	create_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				philosopher_routine, &data->philos[i]) != 0)
			return (write(2, "Failed to create thread\n", 25));
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
		return (write(2, "Failed to create monitor thread\n", 33));
	return (0);
}

void	check_routine(t_philo *philo, bool *simulation_ended)
{
	eat_sleep_routine(philo);
	handle_nbr_of_meals(philo);
	think_routine(philo, false);
	pthread_mutex_lock(&philo->data->mtx);
	*simulation_ended = philo->data->end;
	pthread_mutex_unlock(&philo->data->mtx);
}
