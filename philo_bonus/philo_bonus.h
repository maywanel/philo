/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:57:18 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/11 18:32:32 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
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
//................................................................
# define MAX_PHILO 200
//................................................................
# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIED "died\n"
//...............................................................
# define SEM_PRINT "/print"
# define SEM_FORKS "/forks"
# define SEM_EAT "/eat"
# define SEM_DEAD "/dead"
//...............................................................
typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long				sleep_time;
	long				eat_time;
	long				die_time;
	long				pid;
	long				meal_time;
	long				start_time;
	long				meal_c;
	bool				full;
	bool				death;
	long				last_meal;
	t_data				*data;
}						t_philo;

struct					s_data
{
	int					nbr_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_of_meals;
  int         full;
	long				start_time;
	bool				end;
	t_philo				*philos;
	sem_t				*print;
	sem_t				*forks;
	sem_t				*eat;
	sem_t				*dead;
	sem_t				*stop;
	pid_t				*pids;
};
//...............................................................

void	print_status(t_philo *philo, char *status);
void	philo_sleep(t_data *data, long milliseconds);
long	get_current_time(void);
long	ft_atol(char *str);
char	*valid_input(char *str);
void	init_data(t_data *data, int argc, char **argv);
void  	start_the_dinner(t_data *data);
void 	kill_all_pid(t_data *data, int last);
void	error_print(char *str, t_data *data);
void	wrong_nbr_of_arg(void);

#endif
