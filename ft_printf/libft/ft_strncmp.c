/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:17:55 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/13 12:47:14 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n != 0)
	{
		if (*s1 != *s2++)
		{
			return (*(const unsigned char *)s1 - \
					*(const unsigned char *)(s2 - 1));
		}
		if (*s1++ == '\0')
		{
			break ;
		}
		n--;
	}
	return (0);
}
