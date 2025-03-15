/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:30:28 by moel-mes          #+#    #+#             */
/*   Updated: 2024/11/12 10:41:42 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	p_len(unsigned long n)
{
	int	l;

	l = 0;
	while (n != 0)
	{
		l++;
		n = n / 16;
	}
	return (l);
}

int	print_p(void *p)
{
	int	l;

	l = 0;
	if ((unsigned long)p == 0)
		l += write(1, "0x0", 3);
	else
	{
		l += write(1, "0x", 2);
		print_hex((unsigned long)p, 'x');
		l += p_len((unsigned long)p);
	}
	return (l);
}
