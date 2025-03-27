/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:42:52 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/20 02:13:19 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long ft_atol(char *str)
{
    long num;
    int i;

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

long get_current_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
void	philo_sleep(long milliseconds)
{
    long	start;
    long	current;
    long	elapsed;
    long	remaining;

    if (milliseconds <= 0)
        return;

    start = get_current_time();
    while (1)
    {
        current = get_current_time();
        elapsed = current - start;

        if (elapsed >= milliseconds)
            break;

        remaining = milliseconds - elapsed;

        if (remaining > 10)
            usleep(5000);
        else if (remaining > 1)
            usleep(remaining * 800);
        else
            break;
    }
}

void	sim_start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue ;
}
