/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:28:25 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/18 15:20:10 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	save_fds(int *fd_in, int *fd_out)
{
	*fd_in = dup(0);
	*fd_out = dup(1);
}

void	reset_and_close(int *fd_in, int *fd_out)
{
	dup2(*fd_in, 0);
	dup2(*fd_out, 1);
	close(*fd_in);
	close(*fd_out);
}

int	redir_function(t_tree *node)
{
	t_redir	*tmp;
	int		return_value;

	if (!node->redirs)
		return (0);
	tmp = node->redirs;
	return_value = 0;
	while (tmp)
	{
		if (tmp->type == 6)
			return_value = (redir_in(tmp));
		else if (tmp->type == 5 || tmp->type == 7)
			return_value = (redir_out(tmp));
		else if (tmp->type == HERE_DOC)
			return_value = heredoc_redir(node);
		if (return_value != 0)
			return (return_value);
		tmp = tmp->next;
	}
	return (return_value);
}

int	redir_in(t_redir *redir)
{
	int	fd_in;

	if (access(redir->value, R_OK | F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->value);
		return (1);
	}
	fd_in = open(redir->value, O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->value);
		return (1);
	}
	dup2(fd_in, 0);
	close(fd_in);
	return (0);
}

int	redir_out(t_redir *redir)
{
	int	fd_out;

	if (redir->type == 5)
		fd_out = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == 7)
		fd_out = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->value);
		return (1);	
	}
	if (access(redir->value, W_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->value);
		return (1);
	}
	dup2(fd_out, 1);
	close(fd_out);
	return (0);
}
