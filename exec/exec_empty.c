/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:17:19 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/07 13:41:40 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	command_is_empty(t_tree *node)
{
	t_value_node	*tmp;

	if (!node || !node->n_value)
		return (1);
	tmp = node->n_value;
	while (tmp)
	{
		if (tmp->value && tmp->value[0] != '\0')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	empty_check(t_tree *node)
{
	if (!node || !node->n_value || !node->n_value->value)
		return (1);
	while ((only_spaces(node->n_value->value)
			|| only_tabs(node->n_value->value)) && node->n_value->next)
	{
		node->n_value = node->n_value->next;
	}
	if (!node->n_value->next && (only_spaces(node->n_value->value)
			|| only_tabs(node->n_value->value)))
		return (1);
	return (0);
}
