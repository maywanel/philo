/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:48:30 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/12 09:34:34 by moel-mes         ###   ########.fr       */
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
	int		is_full;

	if (pthread_create(death_watcher, NULL, parent_death_monitor, data) != 0)
	{
		error_print("Failed to create parent monitor thread", data);
		(kill_all_pid(data, data->nbr_of_philos), exit(EXIT_FAILURE));
	}
	while (1)
	{
		sem_wait(data->full_sem);
		is_full = data->full;
		sem_post(data->full_sem);
		if (is_full == 1)
			break ;
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == 0)
			usleep(1000);
		if (pid == -1)
			break ;
	}
	pthread_join(*death_watcher, NULL);
	kill_all_pid(data, data->nbr_of_philos);
}
