/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:34:40 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/23 21:17:54 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	wrong_nbr_of_arg(void)
{
	printf("usage: ./philo");
	printf(" number_of_philosophers");
	printf(" time_to_die");
	printf(" time_to_eat");
	printf(" time_to_sleep");
	printf(" [number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

void	error_print(char *str, t_data *data)
{
	sem_wait(data->print);
	print_error(str);
	print_error("\n");
	sem_post(data->print);
}

void	kill_all_pid(t_data *data, int last)
{
	int	i;

	i = 0;
	if (!data || !data->pids)
		return ;
	while (i < last)
	{
		if (data->pids[i] > 0)
		{
			kill(data->pids[i], SIGKILL);
			waitpid(data->pids[i], NULL, 0);
		}
		i++;
	}
}

void	clean(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->eat);
	sem_close(data->print);
	sem_close(data->meals_completed);
	sem_unlink("/meals_completed");
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_PRINT);
	if (data->philos)
		free(data->philos);
	if (data->pids)
		free(data->pids);
}

void	clean_exit(t_data *data, int exit_code)
{	
	sem_close(data->forks);
	sem_close(data->eat);
	sem_close(data->print);
	sem_close(data->meals_completed);
	free(data->philos);
	free(data->pids);
	exit(exit_code);
}
