/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:48:30 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/23 21:16:26 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_main_loop(t_philo *philo)
{
	while (1)
	{
		if (philo->death)
			clean_exit(philo->data, 0);
		eat_sleep_routine(philo);
		check_number_meals(philo);
		think_routine(philo, false);
	}
}

void	monitor_dinner(t_data *data)
{
	int	status;
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nbr_of_philos)
		{
			if (waitpid(data->philos[i].pid, &status, WNOHANG) > 0)
			{
				kill_all_pid(data, data->nbr_of_philos);
				return ;
			}
			i++;
		}
	}
}
