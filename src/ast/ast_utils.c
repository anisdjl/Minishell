/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:04:40 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/03 15:56:53 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*find_op(t_token *start, t_token *end, t_enum type)
{
	int		subshell;
	t_token	*tmp;
	t_token	*op;

	op = NULL;
	tmp = start;
	subshell = 0;
	while (tmp != end)
	{
		if (tmp->type == L_PARENTHESE)
			subshell++;
		else if (tmp->type == R_PARENTHESE)
			subshell--;
		if (subshell == 0 && tmp->type == type)
			op = tmp;
		tmp = tmp->next;
	}
	return (op);
}

t_token	*ast_eval_op(t_token *start, t_token *end)
{
	t_token	*op_pos;

	op_pos = find_op(start, end, OR);
	if (!op_pos)
		op_pos = find_op(start, end, AND);
	if (!op_pos)
		op_pos = find_op(start, end, PIPE);
	return (op_pos);
}

int	is_subshell_redir(t_token *start, t_token *end)
{
	while (start && start != end)
	{
		if (start->type < HERE_DOC || start->type > APPEND)
			return (0);
		if (!start->next || start->next == end)
			return (0);
		start = start->next->next;
	}
	return (1);
}

void	add_subshell_redirs(t_tree *node, t_token *start, t_token *end)
{
	while (start && start != end)
	{
		add_redir(node, start);
		if (!start->next)
			break ;
		start = start->next->next;
	}
}
