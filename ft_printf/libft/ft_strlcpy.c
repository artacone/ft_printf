/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:24:26 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/16 16:18:51 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		n_left;

	s = src;
	n_left = size;
	if (n_left != 0)
	{
		while (--n_left != 0)
		{
			*dst++ = *s;
			if (*s++ == '\0')
				break ;
		}
	}
	if (n_left == 0)
	{
		if (size != 0)
			*dst = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
