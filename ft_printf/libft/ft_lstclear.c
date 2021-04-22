/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:00:29 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/14 13:34:31 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (lst)
	{
		while (*lst)
		{
			node = *lst;
			*lst = node->next;
			del(node->content);
			free(node);
		}
	}
	lst = NULL;
}
