/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 00:48:11 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/14 01:11:25 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*resi;

	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == NULL)
	{
		return (NULL);
	}
	resi = res;
	while (*s1)
	{
		*resi++ = *s1++;
	}
	while (*s2)
	{
		*resi++ = *s2++;
	}
	*resi = '\0';
	return (res);
}
