/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:42:29 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/15 08:27:29 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*valid_input(char *str)
{
	int		l;
	char	*nbr;
	int		i;

	nbr = str;
	l = 0;
	i = 0;
	while (*str == 32 || (*str >= 8 && *str <= 13))
		str++;
	if (*str == '-')
		i = write(2, "only positive numbers\n", 23);
	else if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		i = write(2, "only numeric\n", 14);
	nbr = str;
	while (ft_isdigit(*str++))
		l++;
	if (l > 10 && ft_atoi(nbr) < 0)
		i = write(2, "number is too high\n", 20);
	if (i)
		return (NULL);
	return (nbr);
}
