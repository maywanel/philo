/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:57:18 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/05 02:15:13 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h> 
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
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
typedef struct s_data t_data;

typedef struct s_philo
{
    int				id;
    int				eat_count;
    long			last_eat_time;
    t_data	*data;
}	t_philo;

struct s_data
{
    int				nbr_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nbr_of_meals;
    long			start_time;
    bool            end;
    t_philo			*philos;
    sem_t			*print;
    sem_t			*forks;
    sem_t			*eat;
    sem_t			*dead;
};
//...............................................................

#endif