/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:12:17 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 15:25:00 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_pipe_subshell2(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_extra_fds(node, *fd_in, *fd_out);
	if (redir_for_pipes(node, fd_in, fd_out) != 0)
	{
		free_env(&env);
		ft_free_all_malloc();
		exit(1);
	}
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
}

void	exit_wrong_pid(t_env *env)
{
	ft_free_all_malloc();
	free_env(&env);
	exit(EXIT_FAILURE);
}

void	check_empty_redirs(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	if (redir_for_pipes(node, fd_in, fd_out) != 0)
	{
		free_env(&env);
		ft_free_all_malloc();
		exit(1);
	}
	if (command_is_empty(node))
	{
		free_env(&env);
		ft_free_all_malloc();
		close_pipe();
		exit (0);
	}
}
