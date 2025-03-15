/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:42:31 by moel-mes          #+#    #+#             */
/*   Updated: 2024/11/12 10:41:52 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_u(unsigned int u)
{
	char	buffer[12];
	char	*n;
	int		width;

	n = buffer;
	if (u == 0)
		*n++ = '0';
	else
	{
		while (u != 0)
		{
			*n++ = '0' + (u % 10);
			u /= 10;
		}
	}
	width = n - buffer;
	while (n > buffer)
		ft_putchar(*--n);
	return (width);
}
