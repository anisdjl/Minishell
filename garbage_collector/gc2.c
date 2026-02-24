/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:22:37 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/24 15:27:24 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	ft_lstadd_back_gc(t_list **lst, t_list *new_node)
{
	t_list	*ptr;

	if ((*lst) == NULL)
		*lst = new_node;
	else
	{
		ptr = *lst;
		while (ptr->next)
		{
			ptr = ptr->next;
		}
		ptr->next = new_node;
	}
}

t_list	*ft_lstnew_gc(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
