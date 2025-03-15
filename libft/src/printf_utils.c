/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:42:43 by moel-mes          #+#    #+#             */
/*   Updated: 2024/11/12 10:42:07 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	numbr_len(unsigned int n, int base)
{
	int	i;

	i = 0;
	if (n < 10)
		return (1);
	while (n >= 1)
	{
		i++;
		n /= base;
	}
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[len])
	{
		ft_putchar(str[len]);
		len++;
	}
	return (len);
}

int	ft_putnbr(int n)
{
	unsigned int	nb;
	int				sign;

	sign = 0;
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
	{
		sign = 1;
		ft_putchar('-');
		nb = -n;
	}
	else
		nb = n;
	if (nb < 10)
	{
		ft_putchar(nb + '0');
		return (1 + sign);
	}
	else
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
	return (numbr_len(nb, 10) + sign);
}
