/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:43:25 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/09 18:42:56 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*valid_input(char *str)
{
	int		l;
	char	*nbr;

	nbr = str;
	l = 0;
	while (*str == 32 || (*str >= 8 && *str <= 13))
		str++;
	if (*str == '-')
		error_print("only positive numbers\n", NULL);
	else if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
	{
		ft_printf("%s", str);
		error_print(" not a number\n", NULL);
	}
	nbr = str;
	while (ft_isdigit(*str++))
		l++;
	if (l > 10 && ft_atoi(nbr) < 0)
		error_print("number is too high\n", NULL);
	return (nbr);
}
