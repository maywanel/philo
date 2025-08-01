/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:57:18 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/11 19:41:15 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SEM_FORKS "/sem_forks"
# define SEM_EAT "/sem_eat"
# define SEM_DEAD "/sem_dead"
# define SEM_PRINT "/sem_print"
# define SEM_FULL "/sem_full"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

# define MAX_PHILO 200

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nbr_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					nbr_of_meals;
	long				start_time;
	int					full;
	sem_t				*forks;
	sem_t				*eat;
	sem_t				*dead;
	sem_t				*print;
	sem_t				*full_sem;
	t_philo				*philos;
	pid_t				*pids;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					meal_c;
	long				last_meal;
	int					death;
	pid_t				pid;
	t_data				*data;
}						t_philo;

/* Utils */
long					ft_atol(char *str);
void					print_status(t_philo *philo, char *status);
long					get_current_time(void);
void					philo_sleep(long time);

/* Init */
void					init_philo(t_philo *philo, int id, t_data *data);
void					init_philos(t_philo *philos, t_data *data);
void					init_data(t_data *data, char **argv);

/* Dinner */
void					eat_sleep_routine(t_philo *philo);
void					*death_monitor(void *arg);
void					philo_routine(t_philo *philo);
void					start_the_dinner(t_data *data);
void					think_routine(t_philo *philo, bool silent);
void					grab_forks(t_philo *philo);
void					lone_philo_routine(t_philo *philo);
void					*parent_death_monitor(void *arg);
void					philo_main_loop(t_philo *philo);
int						start_philo_process(t_data *data, int i);

/* Clean */
void					wrong_nbr_of_arg(void);
void					error_print(char *str, t_data *data);
void					kill_all_pid(t_data *data, int last);
void					clean(t_data *data);

char					*valid_input(char *str);
void					print_error(char *str);
void					init_args(t_data *data, char **argv);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);

#endif
