/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utlis_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:46:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/05 19:53:44 by moel-mes         ###   ########.fr       */
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

void	init_dinner(t_data *data)
{
	int	i;

	data->start_time = get_current_time();
	data->end = false;
	data->full_philos = 0;
	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meal_c = 0;
		i++;
	}
}

void	create_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				philosopher_routine, &data->philos[i]) != 0)
			error_exit("Failed to create thread\n");
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
		error_exit("Failed to create monitor thread\n");
}
