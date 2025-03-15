/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:25:03 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/28 12:49:37 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*s;

	if (s1)
		len = ft_strlen(s1);
	else
		len = 0;
	if (s2)
		len += ft_strlen(s2);
	else
		len += 0;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	i = -1;
	j = 0;
	while (s1 && s1[++i])
		s[i] = s1[i];
	while (s2 && s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}
