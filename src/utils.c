/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:42:52 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/15 02:45:15 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_atol(char *str)
{
    long num;
    int i;

    num = 0;
    i = 0;
    str = valid_input(str);
    while (ft_isdigit(str[i]))
    {
        num = (num * 10) + (str[i] - 48);
        i++;
    }
    return (num);
}
