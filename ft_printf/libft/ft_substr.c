/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 00:15:49 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/16 15:55:14 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (start > ft_strlen(s))
	{
		start = ft_strlen(s);
	}
	subs = (char *)malloc(len + 1);
	if (subs == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[start] != '\0' && len-- != 0)
	{
		subs[i++] = s[start++];
	}
	subs[i] = '\0';
	return (subs);
}
