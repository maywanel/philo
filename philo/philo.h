/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:10:41 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/12 18:23:20 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200
# define FORK " has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define DIED " died\n"

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
	long				last_meal;
}						t_philo;

struct					s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_of_meals;
	long				start_time;
	bool				end;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		print;
	pthread_mutex_t		mtx;
	int					full_philos;
};

int						init_data(t_data *data, char **av);
void					wrong_nbr_of_arg(void);
long					ft_atol(char *str);
char					*valid_input(char *str);
void					init_forks(t_data *data);
void					init_philos(t_data *data);
void					clean(t_data *data);
int						start_the_dinner(t_data *data);
void					*philosopher_routine(void *arg);
long					get_current_time(void);
void					print_status(t_philo *philo, char *status);
void					philo_sleep(t_data *data, long milliseconds);
int						create_threads(t_data *data, pthread_t *monitor);
void					*monitor_routine(void *data_ptr);
void					acquire_forks(t_philo *philo);
void					handle_nbr_of_meals(t_philo *philo);
void					set_simulation_end(t_data *data);
void					*lone_philo_routine(t_philo *philo);
void					init_dinner(t_data *data);
void					check_routine(t_philo *philo, bool *simulation_ended);
void					eat_sleep_routine(t_philo *philo);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);

#endif
