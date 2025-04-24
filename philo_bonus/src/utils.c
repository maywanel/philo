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
    long elapsed;
    int i;
    t_philo *philo;
    
    start = get_current_time();
    // Find the philosopher in the data structure by matching process ID
    // This allows us to check the death flag while sleeping
    i = 0;
    while (i < data->nbr_of_philos)
    {
        philo = &data->philos[i];
        if (philo->pid == getpid())
            break;
        i++;
    }
    
    // Loop until the time has passed, checking for death periodically
    elapsed = 0;
    while (elapsed < time)
    {
        // Check if this is a philosopher process and if death flag is set
        // This allows us to detect death even while sleeping or eating
        // and perform proper cleanup before exiting
        if (i < data->nbr_of_philos && philo->death)
        {
            clean(data);
            exit(1);
        }
        
        // Sleep in smaller chunks to check for death more frequently
        usleep(500);
        
        current = get_current_time();
        elapsed = current - start;
    }
}
