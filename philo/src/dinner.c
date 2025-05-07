/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:00:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/07 11:23:53 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_sleep_routine(t_philo *philo)
{
	acquire_forks(philo);
	if (philo->data->end)
    {
        pthread_mutex_unlock(&(philo->left_fork->fork));
        pthread_mutex_unlock(&(philo->right_fork->fork));
        return;
    }
	print_status(philo, EAT);
	pthread_mutex_lock(&(philo->data->die_time_mtx));
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&(philo->data->die_time_mtx));
	philo_sleep(philo->data, philo->eat_time);
	pthread_mutex_lock(&(philo->data->meal_check));
	if (philo->data->nbr_of_meals != -1)
		philo->meal_c++;
	pthread_mutex_unlock(&(philo->data->meal_check));
	print_status(philo, SLEEP);
	pthread_mutex_unlock(&(philo->left_fork->fork));
	pthread_mutex_unlock(&(philo->right_fork->fork));
	philo_sleep(philo->data, philo->sleep_time);
}

void	*philosopher_routine(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	if (philo->data->nbr_of_meals == 0)
		return (NULL);
	pthread_mutex_lock(&philo->data->die_time_mtx);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->die_time_mtx);
	if (philo->die_time == 0)
	{
		philo->death = true;
		set_simulation_end(philo->data);
		return (NULL);
	}
	if (philo->data->philo_nbr == 1)
		return (lone_philo_routine(philo));
	else if (!(philo->id % 2))
		usleep(500);
	while (!philo->data->end)
	{
		eat_sleep_routine(philo);
		handle_nbr_of_meals(philo);
		think_routine(philo, false);
	}
	return (NULL);
}

static int	check_philosopher_death(t_data *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->die_time_mtx);
	time_since_last_meal = get_current_time() - data->philos[i].last_meal;
	if (time_since_last_meal > (long)data->philos[i].die_time
		|| data->philos[i].death)
	{
		pthread_mutex_unlock(&data->die_time_mtx);
		print_status(&data->philos[i], DIED);
		set_simulation_end(data);
		return (1);
	}
	pthread_mutex_unlock(&data->die_time_mtx);
	return (0);
}

void	*monitor_routine(void *data_ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_ptr;
	while (!data->end)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

void	start_the_dinner(t_data *data)
{
	int			i;
	pthread_t	monitor;

	init_dinner(data);
	create_threads(data, &monitor);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			error_exit("Failed to join thread\n");
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		error_exit("Failed to join monitor thread\n");
}
