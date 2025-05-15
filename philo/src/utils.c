/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:42:52 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/15 08:42:51 by moel-mes         ###   ########.fr       */
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
	if (!str)
		return (-1);
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		if (num > 2147483647)
			return (write(2, " is too high\n", 14), -1);
		i++;
	}
	if (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			return (num);
		else
			return (write(2, "only numeric\n", 14), -1);
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
	bool	simulation_ended;

	start = get_current_time();
	while (1)
	{
		test = get_current_time() - start;
		if (test >= milliseconds)
			break ;
		pthread_mutex_lock(&data->mtx);
		simulation_ended = data->end;
		pthread_mutex_unlock(&data->mtx);
		if (simulation_ended)
			break ;
		usleep(200);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (sign * result);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
