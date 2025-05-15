/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:37:14 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/15 08:50:35 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wrong_nbr_of_arg(void)
{
	printf("usage: ./philo");
	printf(" number_of_philosophers");
	printf(" time_to_die");
	printf(" time_to_eat");
	printf(" time_to_sleep");
	printf(" [number_of_times_each_philosopher_must_eat]\n");
}

void	clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->mtx);
	free(data->philos);
	free(data->forks);
}
