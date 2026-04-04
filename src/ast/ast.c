/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:18:42 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/04 14:32:42 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tree	*ast_value_node(t_token *start, t_token *end)
{
	t_tree			*node;
	t_value_node	*new_value;
	int				i;

	i = 0;
	node = ft_malloc(sizeof(t_tree), 1);
	node->type = WORD;
	while (start && start != end)
	{
		if (start->type == WORD)
		{
			new_value = ft_lstnew_value(start->value);
			new_value->type = start->type;
			new_value->flag = start->flag;
			ft_lstadd_back_value(&node->n_value, new_value);
		}
		else if (start->type >= 4 && start->type <= 7)
		{
			add_redir(node, start);
			if (start->next)
				start = start->next;
		}
		start = start->next;
	}
	return (node);
}

t_tree	*ast_op_node(t_token *op_pos)
{
	t_tree			*node;
	t_value_node	*new_value;

	node = ft_malloc(sizeof(t_tree), 1);
	new_value = ft_lstnew_value(op_pos->value);
	new_value->type = op_pos->type;
	new_value->flag = op_pos->flag;
	ft_lstadd_back_value(&node->n_value, new_value);
	node->type = op_pos->type;
	node->data = op_pos;
	return (node);
}

t_tree	*ast(t_token *start, t_token *end)
{
	t_tree	*node;
	t_token	*op_pos;
	t_token	*match;

	node = NULL;
	op_pos = NULL;
	if (start == NULL || start == end)
		return (NULL);
	if (start->type == L_PARENTHESE)
	{
		match = ast_find_subparent(start);
		if (match && is_subshell_redir(match->next, end))
		{
			node = ast_build_subshell(start, match);
			add_subshell_redirs(node, match->next, end);
			return (node);
		}
	}
	op_pos = ast_eval_op(start, end);
	if (!op_pos)
		return (ast_value_node(start, end));
	node = ast_op_node(op_pos);
	node->left = ast(start, op_pos);
	node->right = ast(op_pos->next, end);
	return (node);
}

t_tree	*ast_launcher(t_token *token, t_env *env)
{
	t_tree	*s_ast;

	if (!token)
		return (NULL);
	if (!ast_check(token))
	{
		env->exit_status->exit_status = 2;
		return (NULL);
	}
	s_ast = ast(token, NULL);
	return (s_ast);
}
