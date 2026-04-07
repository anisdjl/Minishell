/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:03:24 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 12:32:58 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*generate_herdoc_name(int index)
{
	char	*name;
	char	*number;

	number = ft_itoa(index);
	name = ft_strjoin(".heredoc_tmp_", number);
	return (name);
}

int	here_doc(t_tree *node, t_env *env)
{
	t_redir	*tmp;
	int		return_value;

	return_value = 0;
	if (!node->redirs)
		return (0);
	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			return_value = create_file(node, env, tmp);
			return_value = write_in_file(node, env, tmp);
		}
		tmp = tmp->next;
	}
	env->exit_status->exit_status = return_value;
	return (return_value);
}

int	create_file(t_tree *node, t_env *env, t_redir *redir)
{
	static int	i = 0;

	redir->file_name = generate_herdoc_name(i);
	i++;
	env->fd_w = open(redir->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (env->fd_w < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("");
		return (1);
	}
	if (node->fd_r > 2)
		close(node->fd_r);
	node->fd_r = open(redir->file_name, O_RDONLY);
	if (node->fd_r < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("");
		return (1);
	}
	unlink(redir->file_name);
	return (0);
}

int	heredoc_redir(t_tree *node)
{
	int	value;

	value = dup2(node->fd_r, 0);
	if (value < 0)
	{
		perror("Error: ");
		return (value);
	}
	close(node->fd_r);
	return (0);
}

int	pre_exec(t_tree *node, t_env *env)
{
	int	return_value;

	return_value = 0;
	if (!node)
		return (0);
	if (node && (node->type == AND || node->type == OR || node->type == PIPE))
	{
		if (node->left)
			return (pre_exec(node->left, env));
		if (node->right)
			return (pre_exec(node->right, env));
	}
	else if (node && node->left && node->type == SUBSHELL)
		return (pre_exec(node->left, env));
	else if (node && node->type == WORD)
		return (here_doc(node, env));
	return (return_value);
}
