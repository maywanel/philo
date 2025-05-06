/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:20:58 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/06 16:54:34 by moel-mes         ###   ########.fr       */
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
		perror("sem_open failure for forks");
		exit(EXIT_FAILURE);
	}
	data->eat = sem_open(SEM_EAT, O_CREAT, 0644, data->nbr_of_philos);
	if (data->eat == SEM_FAILED)
	{
		perror("sem_open failure for eat");
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
		perror("sem_open failure for dead");
		sem_close(data->forks);
		sem_close(data->eat);
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_EAT);
		exit(EXIT_FAILURE);
	}
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		perror("sem_open failure for print");
		sem_close(data->forks);
		sem_close(data->eat);
		sem_close(data->dead);
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_EAT);
		sem_unlink(SEM_DEAD);
		exit(EXIT_FAILURE);
	}
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->nbr_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->nbr_of_philos > MAX_PHILO)
	{
		perror("200 philosophers at maximum");
		exit(EXIT_FAILURE);
	}
	if (data->nbr_of_philos < 1)
	{
		perror("number of philosophers is too low");
		exit(EXIT_FAILURE);
	}
	if (argc == 6)
		data->nbr_of_meals = ft_atol(argv[5]);
	else
		data->nbr_of_meals = -1;
	data->start_time = get_current_time();
	data->full = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
	{
		perror("malloc failure for philos");
		exit(EXIT_FAILURE);
	}
	data->pids = calloc(data->nbr_of_philos, sizeof(pid_t));
	if (!data->pids)
	{
		perror("malloc failure for pids");
		(free(data->philos), exit(EXIT_FAILURE));
	}
	init_fork_and_eat_sems(data);
	init_dead_and_print_sems(data);
	init_philos(data->philos, data);
}
