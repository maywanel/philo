/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:18:49 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/28 22:08:58 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(const char *str, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			w++;
		i++;
	}
	return (w);
}

static char	*create_word(const char *s, int *i, char c)
{
	int		k;
	char	*str;

	while (s[*i] == c)
		(*i)++;
	k = *i;
	while (s[k] != c && s[k] != '\0')
		k++;
	str = malloc((k - *i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	k = 0;
	while (s[*i] && s[*i] != c)
	{
		str[k++] = s[*i];
		(*i)++;
	}
	str[k] = '\0';
	return (str);
}

static void	free_words(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(str[i++]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		w;
	char	**str;
	int		p;
	int		i;

	if (!s)
		return (NULL);
	w = ft_word_count(s, c);
	str = malloc((w + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	p = 0;
	i = 0;
	while (p < w)
	{
		str[p] = create_word(s, &i, c);
		if (!str[p])
		{
			free_words(str, p);
			return (NULL);
		}
		p++;
	}
	str[p] = NULL;
	return (str);
}
