/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:42:38 by moel-mes          #+#    #+#             */
/*   Updated: 2024/11/12 10:41:07 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char s, va_list ar)
{
	int	l;

	l = 0;
	if (s == 'c')
		l += ft_putchar(va_arg(ar, int));
	else if (s == 's')
		l += ft_putstr(va_arg(ar, char *));
	else if (s == 'd' || s == 'i')
		l += ft_putnbr(va_arg(ar, int));
	else if (s == 'u')
		l += ft_print_u(va_arg(ar, unsigned int));
	else if (s == 'x' || s == 'X')
		l += print_hex(va_arg(ar, unsigned int), s);
	else if (s == 'p')
		l += print_p(va_arg(ar, void *));
	else if (s == '%')
		l += ft_putchar('%');
	else
		l += ft_putchar(s);
	return (l);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	ar;
	int		l;

	l = 0;
	i = 0;
	va_start(ar, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (s[i + 1] != '\0')
				l += print_format(s[++i], ar);
		}
		else
			l += ft_putchar(s[i]);
		i++;
	}
	va_end(ar);
	return (l);
}
