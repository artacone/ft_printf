/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 10:36:24 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/14 11:00:15 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ncheck(int n, char *digits, int *i)
{
	unsigned int	un;

	digits[0] = 0;
	if (n < 0)
	{
		digits[0] = '-';
		un = -n;
		return (un);
	}
	un = n;
	if (un == 0)
	{
		digits[1] = '0';
		*i = 2;
	}
	return (un);
}

void	ft_putnbr_fd(int n, int fd)
{
	char			digits[11];
	char			res[11];
	int				i;
	unsigned int	un;

	i = 1;
	un = ncheck(n, digits, &i);
	while (un)
	{
		digits[i++] = un % 10 + '0';
		un /= 10;
	}
	if (digits[0] == '-')
		res[un++] = '-';
	while (i > 1)
		res[un++] = digits[--i];
	write(fd, res, un);
}
