/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:44:43 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/14 19:06:06 by moel-mes         ###   ########.fr       */
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

void print_status(t_philo *philo, char *status)
{
    long timestamp;
    
    sem_wait(philo->data->print);
    timestamp = get_current_time() - philo->data->start_time;
    
    printf("%ld %d %s\n", timestamp, philo->id, status);
    if (ft_strncmp(status, DIED, 10) != 0)
        sem_post(philo->data->print);
}

long get_current_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void philo_sleep(t_data *data, long time)
{
    long start;
    long current;
    (void)data;
    
    start = get_current_time();
    while (1)
    {
        current = get_current_time();
        if (current - start >= time)
            break;
        usleep(100);
    }
}
