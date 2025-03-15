/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 02:47:04 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/28 12:51:41 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(unsigned int n)
{
	if (n <= 9)
		return (1);
	return (nbr_len(n / 10) + 1);
}

static char	*create_str(unsigned int nb, char *str, int i, int sign)
{
	if (sign == -1)
		str[i + 1] = '\0';
	else
		str[i] = '\0';
	if (str[0] != '-')
		i--;
	while (i >= 0 && str[i] != '-')
	{
		str[i] = '0' + (nb % 10);
		nb /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	long	nb;
	int		i;

	sign = 1;
	nb = n;
	if (nb < 0)
	{
		sign = -1;
		nb = -nb;
	}
	if (nb == 0)
		return (ft_strdup("0"));
	i = nbr_len(nb);
	if (sign == -1)
		str = ft_calloc((i + 2), sizeof(char));
	else
		str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (sign < 0)
		str[0] = '-';
	return (create_str(nb, str, i, sign));
}
