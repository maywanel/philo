/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:20:58 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/21 14:44:39 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	clean_all_sems(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->eat);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_EAT);
}

static void	init_fork_and_eat_sems(t_data *data)
{
	(sem_unlink(SEM_PRINT), sem_unlink(SEM_FORKS), sem_unlink(SEM_EAT));
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->nbr_of_philos);
	if (data->forks == SEM_FAILED)
		(print_error("sem_open failure for forks\n"), exit(EXIT_FAILURE));
	data->eat = sem_open(SEM_EAT, O_CREAT, 0644, 1);
	if (data->eat == SEM_FAILED)
	{
		(sem_close(data->forks), sem_unlink(SEM_FORKS));
		(print_error("sem_open failure for eat\n"), exit(EXIT_FAILURE));
	}
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		print_error("sem_open failure for print\n");
		(clean_all_sems(data), exit(EXIT_FAILURE));
	}
	data->meals_completed = sem_open("/meals_completed", O_CREAT, 0644, 0);
	if (data->meals_completed == SEM_FAILED)
	{
		print_error("sem_open failure for meals_completed\n");
		(clean_all_sems(data), exit(EXIT_FAILURE));
	}
}

void	init_data(t_data *data, char **argv)
{
	init_args(data, argv);
	if (data->nbr_of_philos > MAX_PHILO)
	{
		print_error("200 philosophers at maximum\n");
		exit(EXIT_FAILURE);
	}
	if (data->nbr_of_philos < 1)
	{
		print_error("number of philosophers is too low\n");
		exit(EXIT_FAILURE);
	}
	data->start_time = get_current_time();
	data->full = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		(print_error("malloc failure for philos\n"), exit(EXIT_FAILURE));
	data->pids = calloc(data->nbr_of_philos, sizeof(pid_t));
	if (!data->pids)
	{
		free(data->philos);
		(print_error("malloc failure for pids\n"), exit(EXIT_FAILURE));
	}
	init_fork_and_eat_sems(data);
	init_philos(data->philos, data);
}
