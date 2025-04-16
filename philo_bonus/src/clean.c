/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:34:40 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/14 04:24:33 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wrong_nbr_of_arg(void)
{
	ft_printf("USAGE: ./philo");
	ft_printf(" number_of_philosophers");
	ft_printf(" time_to_die");
	ft_printf(" time_to_eat");
	ft_printf(" time_to_sleep");
	ft_printf(" [number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

void error_print(char *str, t_data *data)
{
  sem_wait(data->print);
  perror(str);
  sem_post(data->print);
}

void kill_all_pid(t_data *data, int last)
{
  int i;

  i = 1;
  if (!data || !data->pids)
    return ;
  while (i < last)
  {
    if (data->pids[i] > 0)
      kill(data->pids[i], SIGKILL);
    i++;
  }
}

void clean(t_data *data)
{
  sem_close(data->forks);
  sem_close(data->eat);
  sem_close(data->dead);
  sem_close(data->print);
  sem_unlink(SEM_FORKS);
  sem_unlink(SEM_EAT);
  sem_unlink(SEM_DEAD);
  sem_unlink(SEM_PRINT);
  free(data->philos);
  free(data->pids);
}
