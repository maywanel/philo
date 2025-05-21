/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:44:31 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/21 15:10:32 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	think_routine(t_philo *philo, bool silent)
{
	long	time_to_think;

	time_to_think = (philo->data->time_to_die - (get_current_time()
				- philo->last_meal) - philo->data->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > philo->data->time_to_die)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_status(philo, THINK);
	philo_sleep(philo->data, time_to_think);
}

void	check_number_meals(t_philo *philo)
{
	sem_wait(philo->data->eat);
	if (philo->data->nbr_of_meals > 0
		&& philo->meal_c >= philo->data->nbr_of_meals)
	{
		if (philo->reported_full == false)
		{
			philo->reported_full = true;
			sem_post(philo->data->meals_completed);
		}
	}
	sem_post(philo->data->eat);
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
