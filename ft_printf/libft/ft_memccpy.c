/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 00:33:10 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/13 12:44:38 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		uc;

	d = dst;
	s = src;
	uc = c;
	while (n-- != 0)
	{
		*d++ = *s;
		if (*s++ == uc)
		{
			return (d);
		}
	}
	return (NULL);
}
