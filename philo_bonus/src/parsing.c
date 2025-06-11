/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:43:25 by moel-mes          #+#    #+#             */
/*   Updated: 2025/06/11 19:03:39 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	print_error(char *str)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	exit(EXIT_FAILURE);
}

char	*valid_input(char *str)
{
	int		l;
	char	*nbr;

	nbr = str;
	l = 0;
	while (*str == 32 || (*str >= 8 && *str <= 13))
		str++;
	if (*str == '-')
		print_error("only positive numbers\n");
	else if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
	{
		printf("%s", str);
		print_error(" not numeric\n");
	}
	nbr = str;
	while (ft_isdigit(*str++))
		l++;
	if (l > 10 && ft_atoi(nbr) < 0)
		print_error("number is too high\n");
	return (nbr);
}
