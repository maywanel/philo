/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:44:43 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/11 17:50:35 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		i++;
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

	start = get_current_time();
	(void) data;
	while (1)
	{
		test = get_current_time() - start;
		if (test >= milliseconds)
			break ;
		usleep(100);
	}
}

void print_status(t_philo *philo, char *status)
{
    sem_wait(philo->data->print);
    printf("%ld %d %s", get_current_time() - philo->data->start_time, 
           philo->id, status);
    sem_post(philo->data->print);
}

