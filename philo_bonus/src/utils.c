/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:44:43 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/11 19:48:02 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
			(print_error("number is too large\n"), exit(1));
		i++;
	}
	if (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			return (num);
		else
		{
			printf("%s", str);
			print_error(" not numeric\n");
		}
	}
	return (num);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	sem_wait(philo->data->print);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	sem_post(philo->data->print);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(long time)
{
	long	start;
	long	current;
	long	elapsed;

	start = get_current_time();
	elapsed = 0;
	while (elapsed < time)
	{
		usleep(100);
		current = get_current_time();
		elapsed = current - start;
	}
}

void	init_args(t_data *data, char **argv)
{
	data->nbr_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->nbr_of_meals = ft_atol(argv[5]);
	else
		data->nbr_of_meals = -1;
}
