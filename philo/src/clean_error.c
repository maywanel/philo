/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:37:14 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/10 21:23:53 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *s)
{
	ft_printf("%s", s);
	exit(1);
}

void	wrong_nbr_of_arg(void)
{
	ft_printf("usage: ./philo");
	ft_printf(" number_of_philosophers");
	ft_printf(" time_to_die");
	ft_printf(" time_to_eat");
	ft_printf(" time_to_sleep");
	ft_printf(" [number_of_times_each_philosopher_must_eat]\n");
	exit(1);
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
	pthread_mutex_destroy(&data->mtx);
	free(data->philos);
	free(data->forks);
}
