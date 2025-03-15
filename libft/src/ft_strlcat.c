/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:09:55 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/28 12:49:32 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen >= size)
		return (size + slen);
	i = dlen;
	while (i < size - 1 && src[i - dlen])
	{
		dst[i] = src[i - dlen];
		i++;
	}
	dst[i] = '\0';
	return (dlen + slen);
}
