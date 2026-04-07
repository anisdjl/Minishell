/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:28:25 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 16:11:33 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redir_return_value(t_redir *tmp, t_redir *next, t_tree *node)
{
	int	return_value;

	return_value = 0;
	if (tmp->type == 6)
		return_value = (redir_in(tmp));
	else if (tmp->type == 5 || tmp->type == 7)
		return_value = (redir_out(tmp));
	else if (tmp->type == HERE_DOC)
	{
		next = tmp->next;
		while (next && next->type != HERE_DOC)
			next = next->next;
		if (!next)
			return_value = heredoc_redir(node);
	}
	return (return_value);
}

int	redir_function(t_tree *node)
{
	t_redir	*tmp;
	t_redir	*next;
	int		return_value;

	next = NULL;
	if (!node->redirs)
		return (0);
	tmp = node->redirs;
	while (tmp)
	{
		return_value = redir_return_value(tmp, next, node);
		if (return_value != 0)
			return (return_value);
		tmp = tmp->next;
	}
	return (return_value);
}

int	redir_is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (1);
	}
	return (0);
}

int	redir_in(t_redir *redir)
{
	int		fd_in;
	char	*path;

	path = strip_quotes_redir(redir->value);
	if (!path)
		return (1);
	if (redir_is_directory(path))
		return (1);
	if (access(path, F_OK | R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		return (1);
	}
	fd_in = open(path, O_RDONLY);
	if (fd_in < 0)
		return (error_message(path));
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		return (1);
	}
	close(fd_in);
	return (0);
}
