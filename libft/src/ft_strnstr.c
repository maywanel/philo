/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:33:05 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/28 12:48:57 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *mother, const char *son, size_t len)
{
	size_t	m_len;
	size_t	s_len;
	size_t	i;

	m_len = ft_strlen(mother);
	s_len = ft_strlen(son);
	if (s_len == 0)
		return ((char *)mother);
	if (s_len > m_len)
		return (NULL);
	i = 0;
	while (mother[i] != '\0' && i < len)
	{
		if (mother[i] == *son && len - i >= s_len && ft_strncmp(&mother[i], son,
				s_len) == 0)
			return ((char *)(mother + i));
		i++;
	}
	return (NULL);
}
