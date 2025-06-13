/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:18:51 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/12 00:15:18 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	lone_philo_routine(t_philo *philo)
{
	philo->data->start_time = get_current_time();
	print_status(philo, FORK);
	usleep(philo->data->time_to_die * 1000);
	sem_wait(philo->data->print);
	printf("%ld %d %s\n", get_current_time() - philo->data->start_time,
		philo->id, DIED);
	sem_post(philo->data->dead);
	exit(1);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	long	current_time;
	long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		current_time = get_current_time();
		sem_wait(philo->data->eat);
		time_since_last_meal = current_time - philo->last_meal;
		if (time_since_last_meal > philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("%ld %d %s\n", get_current_time() - philo->data->start_time,
				philo->id, DIED);
			sem_post(philo->data->eat);
			sem_post(philo->data->dead);
			return (NULL);
		}
		sem_post(philo->data->eat);
		usleep(500);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

	sem_wait(philo->data->eat);
	philo->last_meal = get_current_time();
	sem_post(philo->data->eat);
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
	if (philo->id % 2 == 0)
		usleep(100);
	philo_main_loop(philo);
}

void	start_the_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->nbr_of_philos)
	{
		if (start_philo_process(data, i) == -1)
			return ;
		i++;
	}
	sem_wait(data->dead);
	kill_all_pid(data, data->nbr_of_philos);
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
		philo_routine(&data->philos[i]);
		exit(0);
	}
	return (0);
}
