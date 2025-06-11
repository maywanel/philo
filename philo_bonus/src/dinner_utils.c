/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:44:31 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/11 19:03:20 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_main_loop(t_philo *philo)
{
	while (1)
	{
		eat_sleep_routine(philo);
		if (philo->meal_c > philo->data->nbr_of_meals
			&& philo->data->nbr_of_meals != -1)
		{
			sem_post(philo->data->dead);
			return ;
		}
		print_status(philo, THINK);
	}
}

void	grab_forks(t_philo *philo)
{
	if (sem_wait(philo->data->forks) != 0)
	{
		error_print("Failed to acquire fork", philo->data);
		exit(EXIT_FAILURE);
	}
	print_status(philo, FORK);
	if (sem_wait(philo->data->forks) != 0)
	{
		sem_post(philo->data->forks);
		error_print("Failed to acquire second fork", philo->data);
		exit(EXIT_FAILURE);
	}
	print_status(philo, FORK);
}

void	eat_sleep_routine(t_philo *philo)
{
	grab_forks(philo);
	sem_wait(philo->data->eat);
	philo->last_meal = get_current_time();
	philo->meal_c++;
	sem_post(philo->data->eat);
	print_status(philo, EAT);
	philo_sleep(philo->data, philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	print_status(philo, SLEEP);
	philo_sleep(philo->data, philo->data->time_to_sleep);
}

void	*parent_death_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->dead);
	sem_wait(data->full_sem);
	data->full = 1;
	sem_post(data->full_sem);
	return (NULL);
}
