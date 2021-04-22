/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:01:00 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/17 20:33:52 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char sep)
{
	size_t	wc;

	wc = 0;
	while (*s)
	{
		while (*s == sep)
		{
			s++;
		}
		if (*s)
		{
			wc++;
			while (*s && *s != sep)
			{
				s++;
			}
		}
	}
	return (wc);
}

static char	*ft_trim_word(const char **s, char sep)
{
	char	*word;
	size_t	i;

	i = 0;
	while ((*s)[i] && (*s)[i] != sep)
	{
		i++;
	}
	word = ft_substr(*s, 0, i);
	if (word == NULL)
	{
		return (NULL);
	}
	*s += i;
	return (word);
}

static void	*ft_free_words(char **words, size_t wc)
{
	while (wc--)
	{
		free(words[wc]);
	}
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;

	words = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (words == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words[i] = ft_trim_word(&s, c);
			if (words[i] == NULL)
				return (ft_free_words(words, i));
			i++;
		}
	}
	words[i] = NULL;
	return (words);
}
