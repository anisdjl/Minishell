/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:49:23 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 16:32:41 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	overflow_pos(unsigned long long total, char digit)
{
	if (total > (unsigned long long)LLONG_MAX / 10)
		return (1);
	if (total == (unsigned long long)LLONG_MAX / 10
		&& (unsigned long long)(digit - '0')
			> (unsigned long long)LLONG_MAX % 10)
		return (1);
	return (0);
}

int	overflow_neg(unsigned long long total, char digit)
{
	if (total > 9223372036854775808ULL / 10)
		return (1);
	if (total == 9223372036854775808ULL / 10
		&& (unsigned long long)(digit - '0') > 9223372036854775808ULL % 10)
		return (1);
	return (0);
}

void	exit_too_many_args(t_env *env)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	free_env(&env);
	ft_free_all_malloc();
	close_pipe();
	exit (146);
}

void	close_extra_fds(t_tree *node, int fd_in, int fd_out)
{
	int		fd;
	int		heredoc_fd;
	t_redir	*redir;

	heredoc_fd = -1;
	redir = node->redirs;
	while (redir)
	{
		if (redir->type == HERE_DOC && node->fd_r > 2)
			heredoc_fd = node->fd_r;
		redir = redir->next;
	}
	fd = 3;
	while (fd < 1024)
	{
		if (fd != fd_in && fd != fd_out && fd != heredoc_fd)
			close(fd);
		fd++;
	}
}
