/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:00:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/20 02:25:08 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "philo.h"

bool check_death(t_data data)
{
    int i;
    long current_time;
    long time_diff;
    
    i = 0;
    while (i < data.philo_nbr)
    {
        current_time = get_current_time();
        pthread_mutex_lock(&data.die_time_mtx);
        time_diff = current_time - data.philos[i].last_meal;
        pthread_mutex_unlock(&data.die_time_mtx);
        if (time_diff > data.philos[i].die_time)
        {
            pthread_mutex_lock(&data.print);
            ft_printf("%d %d died\n", get_current_time() - data.start_time, data.philos[i].id);
            pthread_mutex_unlock(&data.print);
            return true;
        }
        i++;
    }
    return false;
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;
    
    while (!data->end)
    {
        if (philo->data->philo_nbr == 1)
        {
            pthread_mutex_lock(&data->print);
            ft_printf("%d %d has taken a fork\n", get_current_time() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print);
            usleep(philo->die_time);
            ft_printf("%d %d died\n", get_current_time() - data->start_time, philo->id);
            return NULL;
        }
        else
        {
            pthread_mutex_lock(&philo->right_fork->fork);
            pthread_mutex_lock(&data->print);
            ft_printf("%d %d has taken a fork\n", get_current_time() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print);
            pthread_mutex_lock(&philo->left_fork->fork);
            pthread_mutex_lock(&data->print);
            ft_printf("%d %d has taken a fork\n", get_current_time() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print);
            pthread_mutex_lock(&data->print);
            ft_printf("%d %d is eating\n", get_current_time() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print);
            pthread_mutex_lock(&data->die_time_mtx);
            philo->last_meal = get_current_time();
            pthread_mutex_unlock(&data->die_time_mtx);
            usleep(philo->eat_time);
            if (check_death(*data))
            {
                pthread_mutex_unlock(&philo->right_fork->fork);
                pthread_mutex_unlock(&philo->left_fork->fork);
                data->end = true;
                return NULL;
            }
            pthread_mutex_unlock(&philo->right_fork->fork);
            pthread_mutex_unlock(&philo->left_fork->fork);
            philo->meal_c--;
            if (philo->meal_c == 0)
                philo->full = true;
            pthread_mutex_lock(&data->print);
            ft_printf("%d %d is sleeping\n", get_current_time() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print);
            usleep(philo->sleep_time);
            pthread_mutex_lock(&data->print);
            ft_printf("%d %d is thinking\n", get_current_time() - data->start_time, philo->id);
            pthread_mutex_unlock(&data->print);
        }
    }
    return NULL;
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    int full_philos;
    long current_time;
    long time_diff;
    
    while (!data->end && data->philo_nbr != 1)
    {
        i = 0;
        full_philos = 0;
        while (i < data->philo_nbr)
        {
            current_time = get_current_time();
            pthread_mutex_lock(&data->die_time_mtx);
            time_diff = current_time - data->philos[i].last_meal;
            pthread_mutex_unlock(&data->die_time_mtx);
            if (time_diff > data->philos[i].die_time)
            {
                pthread_mutex_lock(&data->print);
                ft_printf("%d %d died\n", get_current_time() - data->start_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print);
                data->end = true;
                return (NULL);
            }
            if (data->nbr_of_meals != -1 && data->philos[i].meal_c == 0)
                full_philos++;
            i++;
        }
        if (data->nbr_of_meals != -1 && full_philos == data->philo_nbr)
        {
            data->end = true;
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

void	start_the_dinner(t_data *data)
{
    int i;
    pthread_t monitor_thread;

    i = 0;
    while (i < data->philo_nbr)
    {
        if (pthread_create(&data->philos[i].thread_id, NULL, philosopher_routine, &data->philos[i]) != 0)
            error_exit("Failed to create thread\n");
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
        error_exit("Failed to create monitor thread\n");
    i = 0;
    while (i < data->philo_nbr)
    {
        if (pthread_join(data->philos[i].thread_id, NULL) != 0)
            error_exit("Failed to join thread\n");
        i++;
    }
    if (pthread_join(monitor_thread, NULL) != 0)
        error_exit("Failed to join monitor thread\n");
}