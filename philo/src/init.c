/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:51:24 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/29 18:38:54 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **av)
{
	data->philo_nbr = ft_atol(av[1]);
	if (data->philo_nbr > MAX_PHILO)
		error_exit("200 philo at MAX\n");
	else if (data->philo_nbr == 0)
		error_exit("need at least 1 philo\n");
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (!av[5])
		data->nbr_of_meals = -1;
	else
		data->nbr_of_meals = ft_atol(av[5]);
	data->end = false;
	data->philos = malloc(sizeof(*data->philos) * data->philo_nbr);
	if (!data->philos)
		error_exit("MALLOC FAILED\n");
	data->forks = malloc(sizeof(*data->forks) * data->philo_nbr);
	if (!data->forks)
		(free(data->philos), error_exit("MALLOC FAILED\n"));
	data->start_time = get_current_time();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->die_time_mtx, NULL);
	pthread_mutex_init(&data->death_check, NULL);
	pthread_mutex_init(&data->meal_check, NULL);
	init_philos(data);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	init_forks(data);
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_c = data->nbr_of_meals;
		data->philos[i].full = false;
		data->philos[i].death = false;
		data->philos[i].data = data;
		data->philos[i].die_time = data->time_to_die;
		data->philos[i].eat_time = data->time_to_eat;
		data->philos[i].sleep_time = data->time_to_sleep;
		data->philos[i].right_fork = &data->forks[i];
		if (data->philo_nbr == 1)
			data->philos[i].left_fork = NULL;
		else if (i == data->philo_nbr - 1)
			data->philos[i].left_fork = &data->forks[0];
		else
			data->philos[i].left_fork = &data->forks[i + 1];
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->forks[i].id = i;
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
}
