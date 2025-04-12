/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:56:45 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/09 18:36:18 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		wrong_nbr_of_arg();
	init_data(&data, ac, av);
	start_the_dinner(&data);
	//clean(&data);
}
