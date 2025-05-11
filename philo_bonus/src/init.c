/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:20:58 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/09 18:25:29 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int id, t_data *data)
{
	philo->id = id;
	philo->data = data;
	philo->meal_c = 0;
	philo->last_meal = 0;
	philo->death = 0;
	philo->pid = 0;
}

void	init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		init_philo(&philos[i], i + 1, data);
		i++;
	}
}

static void	init_fork_and_eat_sems(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_EAT);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->nbr_of_philos);
	if (data->forks == SEM_FAILED)
	{
		print_error("sem_open failure for forks\n");
		exit(EXIT_FAILURE);
	}
	data->eat = sem_open(SEM_EAT, O_CREAT, 0644, data->nbr_of_philos);
	if (data->eat == SEM_FAILED)
	{
		print_error("sem_open failure for eat\n");
		sem_close(data->forks);
		sem_unlink(SEM_FORKS);
		exit(EXIT_FAILURE);
	}
}

static void	init_dead_and_print_sems(t_data *data)
{
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_PRINT);
	data->dead = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (data->dead == SEM_FAILED)
	{
		print_error("sem_open failure for dead\n");
		sem_close(data->forks);
		sem_close(data->eat);
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_EAT);
		exit(EXIT_FAILURE);
	}
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		print_error("sem_open failure for print\n");
		sem_close(data->forks);
		sem_close(data->eat);
		sem_close(data->dead);
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_EAT);
		sem_unlink(SEM_DEAD);
		exit(EXIT_FAILURE);
	}
}

void	init_data(t_data *data, char **argv)
{
	init_args(data, argv);
	if (data->nbr_of_philos > MAX_PHILO)
		(print_error("200 philosophers at maximum\n"), exit(EXIT_FAILURE));
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
		print_error("malloc failure for pids\n");
		(free(data->philos), exit(EXIT_FAILURE));
	}
	(init_fork_and_eat_sems(data), init_dead_and_print_sems(data));
	init_philos(data->philos, data);
}
