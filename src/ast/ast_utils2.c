/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:18:38 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/01 18:47:31 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_value_node	*ft_lstnew_value(char *content)
{
	t_value_node	*lst;

	lst = ft_malloc(1, sizeof(t_value_node));
	if (lst == 0)
		return (0);
	lst->value = content;
	lst->next = 0;
	return (lst);
}

void	ft_lstadd_back_value(t_value_node **lst, t_value_node *new)
{
	t_value_node	*cursor;

	cursor = *lst;
	if (cursor)
	{
		while (cursor->next != NULL)
		{
			cursor = cursor->next;
		}
		cursor->next = new;
	}
	else if (!cursor)
		*lst = new;
}
