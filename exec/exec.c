/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:07:42 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/28 17:47:30 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec(t_tree *ast)
{
	int	status;
	
	status = 0;
	if (ast->type == AND)
	{
		status = exec(ast->left);
		if (status == 0)
			return (exec(ast->right));
		return (status);
	}
	else if (ast->type == OR)
	{
		status = exec(ast->left);
		if (status != 0)
			return (exec(ast->right));
		return (status);
	}
	else if (ast->type == PIPE)
		return (handle_pipes(ast));
	else if (ast->type == WORD)
		return (exec_cmd(ast));
	return (1);
}

int	handle_pipes(t_tree *node)
{
	int	*nb_of_pipes;

	if (node->left->type == PIPE)
		exec(node->left);
	else
	{
		if (built_in_cmd(node->left))
			return (exec_built_in(node));
		else
			ft_execve(node);
	}
}

int	exec_cmd()