/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 01:12:24 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/16 21:30:54 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	begin;
	size_t	end;

	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] && ft_strchr(set, s1[begin]))
	{
		begin++;
	}
	while (end > begin && ft_strchr(set, s1[end - 1]))
	{
		end--;
	}
	res = ft_substr(s1, begin, end - begin);
	return (res);
}
