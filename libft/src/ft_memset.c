/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:28:48 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/28 12:50:45 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, int len)
{
	while (--len >= 0)
		*((unsigned char *)(b + len)) = (unsigned char)c;
	return (b);
}
