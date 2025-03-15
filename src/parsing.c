/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:42:29 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/15 02:45:12 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char *valid_input(char *str)
{
    int l;
    char *nbr;

    nbr = str;
    l = 0;
    while (*str == 32 || (*str >= 8 && *str <= 13))
        str++;
    if (*str == '-')
        error_exit("only positive numbers\n");
    else if (*str == '+')
        str++;
    if(!ft_isdigit(*str))
    {
        ft_printf("%s", str);
        error_exit(" not a number\n");
    }
    nbr = str;
    while (ft_isdigit(*str++))
        l++;
    if (l > 10 && ft_atoi(nbr) < 0)
        error_exit("number is too high\n");
    return (nbr);
}
