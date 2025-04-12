/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:20:58 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/11 18:37:01 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int id, t_data *data)
{
    philo->id = id;
    philo->data = data;
    philo->meal_c = 0;
    philo->last_meal = 0;
    philo->death = 0;
    philo->pid = 0;
}
void	init_philos(t_philo *philos, t_data *data)
{
    int i;

    i = 0;
    while (i < data->nbr_of_philos)
    {
        init_philo(&philos[i], i + 1, data);
        i++;
    }
}

void	init_sems(t_data *data)
{
    sem_unlink(SEM_FORKS);
    sem_unlink(SEM_EAT);
    sem_unlink(SEM_DEAD);
    sem_unlink(SEM_PRINT); 

    data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->nbr_of_philos);
    if (data->forks == SEM_FAILED)
    {
      error_print("sem_open failure", data);
      exit(EXIT_FAILURE);
    }
    data->eat = sem_open(SEM_EAT, O_CREAT, 0644, 1);
    if (data->eat == SEM_FAILED)
    {
        error_print("sem_open failure", data);
        exit(EXIT_FAILURE);
    }
    data->dead = sem_open(SEM_DEAD, O_CREAT, 0644, 1);
    if (data->dead == SEM_FAILED)
    {
        error_print("sem_open failure", data);
        exit(EXIT_FAILURE);
    }
}

void	init_data(t_data *data, int argc, char **argv)
{
    data->nbr_of_philos = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if (argc == 6)
        data->nbr_of_meals = atoi(argv[5]);
    else
        data->nbr_of_meals = -1;
    data->start_time = get_current_time();
    data->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
    if (data->print == SEM_FAILED)
    {
        error_print("sem_open failure", data);
        exit(EXIT_FAILURE);
    }
    data->philos = malloc(sizeof(*data->philos) * data->nbr_of_philos);
    if (!data->philos) {
      error_print("malloc failure", data);
      exit(EXIT_FAILURE);
    }
    data->forks = malloc(sizeof(*data->forks) * data->nbr_of_philos);
    if (!data->forks) {
      error_print("malloc failure", data);
      exit(EXIT_FAILURE);
    }
    data->pids = calloc(sizeof(int), data->nbr_of_philos);
    if (!data->pids) {
      error_print("malloc failure", data);
      exit(EXIT_FAILURE);
    }
    init_sems(data);
    init_philos(data->philos, data);
}


