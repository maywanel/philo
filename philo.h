/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:10:41 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/15 03:27:27 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include "libft/libft.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#define MAX_PHILO 200

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx				fork;
	int					id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	long				sleep_time;
	long				eat_time;
	long				die_time;
	long				meal_c;
	bool				full;
	bool				death;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_data				*data;
}						t_philo;

struct					s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_of_meals;
	bool				start;
	bool				end;
	t_fork				*forks;
	t_philo				*philos;
};

void init_data(t_data *data, char **av);
void	wrong_nbr_of_arg();
long ft_atol(char *str);
char *valid_input(char *str);
void error_exit(char *s);
void init_forks(t_data *data);
void init_philos(t_data *data);
void clean(t_data*data);

#endif