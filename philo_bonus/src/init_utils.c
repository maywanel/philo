/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:35:12 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/23 21:13:16 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	init_philo(t_philo *philo, int id, t_data *data)
{
	philo->id = id;
	philo->data = data;
	philo->meal_c = 0;
	philo->last_meal = 0;
	philo->death = 0;
	philo->pid = 0;
	philo->reported_full = false;
}

void	init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		init_philo(&philos[i], i + 1, data);
		i++;
	}
}
