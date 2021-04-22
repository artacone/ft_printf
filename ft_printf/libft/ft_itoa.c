/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 09:23:46 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/16 19:09:32 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_internal(int n, char *digits, int *i)
{
	if (n < 0)
	{
		while (n)
		{
			digits[(*i)++] = -(n % 10) + '0';
			n /= 10;
		}
		digits[(*i)++] = '-';
	}
	else if (n > 0)
	{
		while (n)
		{
			digits[(*i)++] = (n % 10) + '0';
			n /= 10;
		}
	}
	else
	{
		digits[(*i)++] = '0';
	}
}

char	*ft_itoa(int n)
{
	char	digits[11];
	int		i;
	int		j;
	char	*res;

	i = 0;
	ft_itoa_internal(n, digits, &i);
	res = (char *)malloc(i + 1);
	if (res == NULL)
	{
		return (NULL);
	}
	j = 0;
	while (i > 0)
	{
		res[j++] = digits[--i];
	}
	res[j] = '\0';
	return (res);
}
