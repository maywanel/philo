/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:00:00 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/23 16:10:08 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_end(t_data *data)
{
    pthread_mutex_lock(&data->death_check);
    data->end = true;
    pthread_mutex_unlock(&data->death_check);
}

void	print_status(t_philo *philo, char *status)
{
    long	current_time;

    if (philo->data->end)
        return;
    pthread_mutex_lock(&philo->data->print);
    if (!philo->data->end)
    {
        current_time = get_current_time() - philo->data->start_time;
        ft_printf("%d %d%s", current_time, philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->print);
}

static void	eat_sleep_routine(t_philo *philo)
{
    pthread_mutex_lock(&(philo->left_fork->fork));
    print_status(philo, " has taken a fork\n");
    pthread_mutex_lock(&(philo->right_fork->fork));
    print_status(philo, " has taken a fork\n");
    
    print_status(philo, " is eating\n");
    pthread_mutex_lock(&(philo->data->die_time_mtx));
    philo->last_meal = get_current_time();
    pthread_mutex_unlock(&(philo->data->die_time_mtx));
    
    philo_sleep(philo->data, philo->eat_time);
    
    pthread_mutex_lock(&(philo->data->meal_check));
    if (philo->data->nbr_of_meals != -1)
        philo->meal_c++;
    pthread_mutex_unlock(&(philo->data->meal_check));
    
    print_status(philo, " is sleeping\n");
    pthread_mutex_unlock(&(philo->left_fork->fork));
    pthread_mutex_unlock(&(philo->right_fork->fork));
    
    philo_sleep(philo->data, philo->sleep_time);
}

static void	think_routine(t_philo *philo, bool silent)
{
    long	time_to_think;

    pthread_mutex_lock(&philo->data->die_time_mtx);
    time_to_think = (philo->die_time - (get_current_time() - philo->last_meal) 
                    - philo->eat_time) / 2;
    pthread_mutex_unlock(&philo->data->die_time_mtx);
    
    if (time_to_think < 0)
        time_to_think = 0;
    if (time_to_think == 0 && silent == true)
        time_to_think = 1;
    if (time_to_think > 600)
        time_to_think = 200;
    
    if (silent == false)
        print_status(philo, " is thinking\n");
    
    philo_sleep(philo->data, time_to_think);
}

static void	*lone_philo_routine(t_philo *philo)
{
    pthread_mutex_lock(&(philo->right_fork->fork));
    print_status(philo, " has taken a fork\n");
    philo_sleep(philo->data, philo->die_time);
    print_status(philo, " has died\n");
    philo->death = true;
    set_simulation_end(philo->data);
    pthread_mutex_unlock(&(philo->right_fork->fork));
    return (NULL);
}

static void    handle_nbr_of_meals(t_philo *philo)
{
    if (philo->data->nbr_of_meals != -1 && philo->meal_c >= philo->data->nbr_of_meals)
    {
        pthread_mutex_lock(&philo->data->meal_check);
        philo->data->full_philos++;
        pthread_mutex_unlock(&philo->data->meal_check);
        if (philo->data->full_philos == philo->data->philo_nbr)
            set_simulation_end(philo->data);
    }
}

void	*philosopher_routine(void *phi)
{
    t_philo	*philo;

    philo = (t_philo *)phi;
    if (philo->data->nbr_of_meals == 0)
        return (NULL);
    pthread_mutex_lock(&philo->data->die_time_mtx);
    philo->last_meal = philo->data->start_time;
    pthread_mutex_unlock(&philo->data->die_time_mtx);
    if (philo->die_time == 0)
    {
        philo->death = true;
        set_simulation_end(philo->data);
        return (NULL);
    }
    if (philo->data->philo_nbr == 1)
        return (lone_philo_routine(philo));
    else if (!(philo->id % 2))
        think_routine(philo, true);   
    while (!philo->data->end)
    {
        eat_sleep_routine(philo);
        handle_nbr_of_meals(philo);
        think_routine(philo, false);
    }
    return (NULL);
}

void	*monitor_routine(void *data_ptr)
{
    t_data	*data;
    int		i;
    long	time_since_last_meal;

    data = (t_data *)data_ptr;
    while (!data->end)
    {
        i = 0;
        while (i < data->philo_nbr)
        {
            pthread_mutex_lock(&data->die_time_mtx);
            time_since_last_meal = get_current_time() - data->philos[i].last_meal;
            if (time_since_last_meal >= (long)data->philos[i].die_time || data->philos[i].death)
            {
                pthread_mutex_unlock(&data->die_time_mtx);
                print_status(&data->philos[i], " died\n");
                set_simulation_end(data);
                return (NULL);
            }
            pthread_mutex_unlock(&data->die_time_mtx);
            i++;
        }
        usleep(1);
    }
    return (NULL);
}

void	start_the_dinner(t_data *data)
{
    int			i;
    pthread_t	monitor;

    data->start_time = get_current_time();
    data->end = false;
    data->full_philos = 0;
    
    for (i = 0; i < data->philo_nbr; i++)
    {
        data->philos[i].last_meal = data->start_time;
        data->philos[i].meal_c = 0;
    }
        for (i = 0; i < data->philo_nbr; i++)
    {
        if (pthread_create(&data->philos[i].thread_id, NULL, 
                philosopher_routine, &data->philos[i]) != 0)
            error_exit("Failed to create thread\n");
    }
    if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
        error_exit("Failed to create monitor thread\n");
    for (i = 0; i < data->philo_nbr; i++)
    {
        if (pthread_join(data->philos[i].thread_id, NULL) != 0)
            error_exit("Failed to join thread\n");
    }    
    if (pthread_join(monitor, NULL) != 0)
        error_exit("Failed to join monitor thread\n");
}
