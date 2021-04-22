/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:33:24 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/13 12:06:06 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	n;

	n = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else
	{
		sign = 1;
		if (*nptr == '+')
			nptr++;
	}
	while (ft_isdigit(*nptr))
		n = n * 10 + (*nptr++ - '0');
	return (sign * n);
}
