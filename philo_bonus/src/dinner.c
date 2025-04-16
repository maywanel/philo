/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:18:51 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/14 19:11:16 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void think_routine(t_philo *philo, bool silent)
{
    long time_to_think;

    time_to_think = (philo->data->time_to_die - (get_current_time() - philo->last_meal)
            - philo->data->time_to_eat) / 2;
    if (time_to_think < 0)
        time_to_think = 0;
    if (time_to_think > philo->data->time_to_die)
        time_to_think = 0;
    if (time_to_think > 600)
        time_to_think = 200;
    if (silent == false)
        print_status(philo, THINK);
    philo_sleep(philo->data, time_to_think);
}

void check_number_meals(t_philo *philo)
{
    sem_wait(philo->data->eat);
    if (philo->meal_c >= philo->data->nbr_of_meals && philo->data->nbr_of_meals != -1)
    {
        philo->data->full++;
        if (philo->data->full >= philo->data->nbr_of_philos)
        {
            sem_post(philo->data->eat);
            clean(philo->data);
            exit(EXIT_SUCCESS);
        }
    }
    sem_post(philo->data->eat);
}

void grab_forks(t_philo *philo)
{
    if (sem_wait(philo->data->forks) != 0)
    {
        error_print("Failed to acquire fork", philo->data);
        clean(philo->data);
        exit(EXIT_FAILURE);
    }
    print_status(philo, FORK);
    
    if (sem_wait(philo->data->forks) != 0)
    {
        sem_post(philo->data->forks);
        error_print("Failed to acquire second fork", philo->data);
        clean(philo->data);
        exit(EXIT_FAILURE);
    }
    print_status(philo, FORK);
}

void eat_sleep_routine(t_philo *philo)
{
    grab_forks(philo);
    
    sem_wait(philo->data->eat);
    philo->last_meal = get_current_time();
    philo->meal_c++;
    print_status(philo, EAT);
    sem_post(philo->data->eat);
    
    philo_sleep(philo->data, philo->data->time_to_eat);
    
    sem_post(philo->data->forks);
    sem_post(philo->data->forks);
    
    print_status(philo, SLEEP);
    philo_sleep(philo->data, philo->data->time_to_sleep);
}

void *death_monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long current_time;
    long time_since_last_meal;

    while (1)
    {
        sem_wait(philo->data->eat);
        current_time = get_current_time();
        time_since_last_meal = current_time - philo->last_meal;
        
        if (time_since_last_meal >= philo->data->time_to_die)
        {
            print_status(philo, DIED);
            philo->death = 1;
            sem_post(philo->data->eat);
            exit(0);
        }
        sem_post(philo->data->eat);
        usleep(1000);
    }
    return NULL;
}

void lone_philo_routine(t_philo *philo)
{
    print_status(philo, FORK);
    philo_sleep(philo->data, philo->data->time_to_die);
    print_status(philo, DIED);
    clean(philo->data);
    exit(1);
}

void philo_routine(t_philo *philo)
{    
    
    philo->last_meal = get_current_time();
    if (philo->data->nbr_of_philos == 1)
    {
        lone_philo_routine(philo);
        return;
    }
    if (philo->id % 2 != 0)
    think_routine(philo, true);
    while(!philo->death)
    {
        eat_sleep_routine(philo);
        check_number_meals(philo);
        think_routine(philo, false);
    }
}

void start_the_dinner(t_data *data)
{
    pthread_t monitor;
    int i;
    
    i = 0;
    while (i < data->nbr_of_philos)
    {
        data->pids[i] = fork();
        if (data->pids[i] == -1)
        {
            error_print("fork failure", data);
            kill_all_pid(data, i);
            clean(data);
            exit(EXIT_FAILURE);
        }
        else if (data->pids[i] == 0)
        {
            if (pthread_create(&monitor, NULL, death_monitor, &data->philos[i]) != 0)
            {
                error_print("Failed to create monitor thread", data);
                clean(data);
                exit(EXIT_FAILURE);
            }
            philo_routine(&data->philos[i]);
            pthread_join(monitor, NULL);
            clean(data);
            exit(0);
        }
        i++;
        usleep(100);
    }
    while (wait(NULL) != -1)
        ;
}
