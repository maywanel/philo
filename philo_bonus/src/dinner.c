/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:18:51 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/02 08:56:24 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	lone_philo_routine(t_philo *philo)
{
	print_status(philo, FORK);
	usleep(philo->data->time_to_die * 1000);
	print_status(philo, DIED);
	exit(0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	long	current_time;
	long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (!philo->death)
	{
		current_time = get_current_time();
		sem_wait(philo->data->eat);
		time_since_last_meal = current_time - philo->last_meal;
		if (time_since_last_meal > philo->data->time_to_die)
		{
			print_status(philo, DIED);
			sem_post(philo->data->death);
			return (NULL);
		}
		if (philo->death)
			return (NULL);
    	sem_post(philo->data->eat);
		usleep(100);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

	philo->last_meal = get_current_time();
	if (philo->data->nbr_of_philos == 1)
	{
		lone_philo_routine(philo);
		return ;
	}
	if (pthread_create(&monitor, NULL, death_monitor, philo) != 0)
	{
		error_print("Failed to create monitor thread", philo->data);
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(monitor) != 0)
	{
		error_print("Failed to detach monitor thread", philo->data);
		exit(EXIT_FAILURE);
	}
	if (philo->id % 2 != 0)
		usleep(500);
	philo_main_loop(philo);
}

void	start_the_dinner(t_data *data)
{
	int	i;

	i = 0;
	sem_wait(data->death);
	while (i < data->nbr_of_philos)
	{
		if (start_philo_process(data, i) == -1)
			return ;
		i++;
		usleep(100);
	}
	sem_wait(data->death);
	kill_all_pid(data, data->nbr_of_philos - 1);
}

int	start_philo_process(t_data *data, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		error_print("fork failure", data);
		kill_all_pid(data, i);
		exit(EXIT_FAILURE);
	}
	else if (data->pids[i] == 0)
	{
		data->philos[i].pid = data->pids[i];
		philo_routine(&data->philos[i]);
		exit(0);
	}
	else
		data->philos[i].pid = data->pids[i];
	return (0);
}
