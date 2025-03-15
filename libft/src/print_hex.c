/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:45:20 by moel-mes          #+#    #+#             */
/*   Updated: 2024/11/12 10:41:28 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	printx(unsigned long u, char c)
{
	char	*hex;

	if (c == 'x')
		hex = "0123456789abcdef";
	if (c == 'X')
		hex = "0123456789ABCDEF";
	if (u >= 16)
		printx(u / 16, c);
	ft_putchar(hex[u % 16]);
}

int	print_hex(unsigned long u, char c)
{
	printx(u, c);
	return (numbr_len(u, 16));
}
