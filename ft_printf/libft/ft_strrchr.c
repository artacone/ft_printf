/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:03:36 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/13 11:09:38 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	char		ch;

	str = s;
	ch = c;
	while (*str)
	{
		str++;
	}
	while (str >= s)
	{
		if (*str-- == ch)
		{
			return ((char *)str + 1);
		}
	}
	return (NULL);
}
