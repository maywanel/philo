/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:42:52 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/10 21:11:09 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	str = valid_input(str);
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		if (num > 2147483647)
			error_exit("number is too high\n");
		i++;
	}
	if (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			return (num);
		else
		{
			ft_printf("%s", str);
			error_exit(" numeric\n");
		}
	}
	return (num);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(t_data *data, long milliseconds)
{
	long	start;
	long	test;

	pthread_mutex_lock(&data->mtx);
	start = get_current_time();
	while (!data->end)
	{
		test = get_current_time() - start;
		if (test >= milliseconds)
			break ;
		usleep(200);
	}
	pthread_mutex_unlock(&data->mtx);
}
