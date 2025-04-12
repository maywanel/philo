/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:35:05 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/11 18:19:01 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->death_check);
	data->end = true;
	pthread_mutex_unlock(&data->death_check);
}

void	print_status(t_philo *philo, char *status)
{
	long	current_time;

	if (philo->data->end)
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->end)
	{
		current_time = get_current_time() - philo->data->start_time;
		ft_printf("%d %d%s", current_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork->fork));
	print_status(philo, FORK);
	philo_sleep(philo->data, philo->die_time);
	print_status(philo, DIED);
	philo->death = true;
	set_simulation_end(philo->data);
	pthread_mutex_unlock(&(philo->right_fork->fork));
	return (NULL);
}

void	handle_nbr_of_meals(t_philo *philo)
{
	if (philo->data->nbr_of_meals != -1
		&& philo->meal_c >= philo->data->nbr_of_meals)
	{
		pthread_mutex_lock(&philo->data->meal_check);
		philo->data->full_philos++;
		pthread_mutex_unlock(&philo->data->meal_check);
		if (philo->data->full_philos == philo->data->philo_nbr)
			set_simulation_end(philo->data);
	}
}

void	think_routine(t_philo *philo, bool silent)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->data->die_time_mtx);
	time_to_think = (philo->die_time - (get_current_time() - philo->last_meal)
			- philo->eat_time) / 2;
	pthread_mutex_unlock(&philo->data->die_time_mtx);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think + philo->eat_time >= philo->die_time)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_status(philo, THINK);
	philo_sleep(philo->data, time_to_think);
}
