/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:48:30 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/29 08:49:49 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_main_loop(t_philo *philo)
{
	while (1)
	{
		if (philo->death)
		{
			clean(philo->data);
			exit(1);
		}
		eat_sleep_routine(philo);
		check_number_meals(philo);
		think_routine(philo, false);
	}
}

void	monitor_dinner(t_data *data, pthread_t *death_watcher)
{
	int		status;
	pid_t	pid;

	if (pthread_create(death_watcher, NULL, parent_death_monitor, data) != 0)
	{
		error_print("Failed to create parent monitor thread", data);
		kill_all_pid(data, data->nbr_of_philos);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (data->full == 1)
			break ;
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == 0)
		{
			usleep(1000);
			continue ;
		}
		if (pid == -1)
			break ;
	}
	pthread_join(*death_watcher, NULL);
	kill_all_pid(data, data->nbr_of_philos);
}
