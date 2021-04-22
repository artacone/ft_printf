/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 00:49:22 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/16 15:03:03 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (n == 0 || dest == src)
		return (dest);
	if (dest < src)
	{
		d = dest;
		s = src;
		while (n-- != 0)
		{
			*d++ = *s++;
		}
	}
	else
	{
		d = dest + (n - 1);
		s = src + (n - 1);
		while (n-- != 0)
		{
			*d-- = *s--;
		}
	}
	return (dest);
}
