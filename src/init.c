/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:51:24 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/15 17:38:32 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **av)
{
	data->philo_nbr = ft_atol(av[1]);
	if (data->philo_nbr >  MAX_PHILO)
		error_exit("200 philo at MAX\n");
	else if (data->philo_nbr == 0)
		error_exit("need at least 1 philo\n");
	data->time_to_die = ft_atol(av[2]) * 1000;
	data->time_to_eat = ft_atol(av[3]) * 1000;
	data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (data->time_to_die > 60000
			|| data->time_to_eat  > 60000
			|| data->time_to_sleep > 60000)
			error_exit("u put a time more than 60ms");
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
	init_philos(data);
}

void init_philos(t_data *data)
{
	int i;

	i = 0;
	init_forks(data);
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i;
		data->philos[i].meal_c = data->nbr_of_meals;
		data->philos[i].full = false;
		data->philos[i].death = false;
		data->philos[i].data = data;
		data->philos[i].die_time = data->time_to_die;
		data->philos[i].eat_time = data->time_to_eat;
		data->philos[i].sleep_time = data->time_to_sleep;
		data->philos[i].right_fork = &data->forks[i];
		if (i == data->philo_nbr - 1)
			data->philos[i].left_fork = &data->forks[0];
		else
			data->philos[i].left_fork = &data->forks[i + 1];
		i++;
	}
}
void init_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->forks[i].id  = i;
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
}