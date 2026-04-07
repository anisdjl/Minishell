/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:07:40 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 15:08:09 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redir_for_pipes(t_tree *node, int *fd_in, int *fd_out)
{
	t_redir	*tmp;
	int		return_value;

	return_value = 0;
	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->type == 6)
			return_value = (redir_in_pipe(tmp, fd_in));
		else if (tmp->type == 5 || tmp->type == 7)
			return_value = (redir_out_pipe(tmp, fd_out));
		else if (tmp->type == 4)
			return_value = heredoc_redir_pipe(node, fd_in);
		if (return_value != 0)
			return (return_value);
		tmp = tmp->next;
	}
	if (*fd_in != 0 && (dup2(*fd_in, STDIN_FILENO) == -1))
		return (1);
	if (*fd_out != 1 && (dup2(*fd_out, STDOUT_FILENO) == -1))
		return (1);
	else
		return (return_value);
}

int	heredoc_redir_pipe(t_tree *node, int *fd)
{
	if (node->fd_r < 0)
		return (1);
	if (*fd != STDIN_FILENO && *fd != node->fd_r)
		close(*fd);
	*fd = node->fd_r;
	return (0);
}

int	redir_in_pipe(t_redir *redir, int *fd_in)
{
	struct stat	st;
	char		*path;

	path = strip_quotes_redir(redir->value);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->value, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (1);
	}
	if (access(path, F_OK | R_OK) == -1)
	{
		perror(redir->value);
		return (1);
	}
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = open(path, O_RDONLY);
	if (*fd_in < 0)
		return (error_message(path));
	return (0);
}

int	redir_out_pipe(t_redir *redir, int *fd_out)
{
	struct stat	st;
	char		*path;

	path = strip_quotes_redir(redir->value);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: Is a directory\n", 2);
		return (1);
	}
	if (*fd_out != 1)
		close (*fd_out);
	if (redir->type == 5)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == 7)
		*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd_out < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}
