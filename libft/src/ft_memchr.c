/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:51:00 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/28 12:50:59 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char	*str;
	unsigned char	byte;
	int				i;

	str = (unsigned char *)s;
	byte = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == byte)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
