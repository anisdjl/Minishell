/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:26:40 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/04 15:39:54 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	echo_cmd_pipe_loop(char **arg, int y)
{
	while (arg[y] && !check_n(arg[y]))
		y++;
	if (y == size_of_table(arg))
		return (0);
	while (arg[y])
	{
		ft_putstr_fd(arg[y], 1);
		if (y < size_of_table(arg) - 1)
			ft_putchar_fd(' ', 1);
		y++;
	}
	return (1);
}

int	echo_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	int	y;
	char	**arg;

	arg = args_to_tab(node->n_value);
	if (arg[1] && !check_n(arg[1])) // option -n
	{
		if (redir_for_pipes(node, fd_in, fd_out))
			exit(1);
		y = 2;
		if (arg[2] == NULL)
			return (0);
		if (!echo_cmd_pipe_loop(arg, y))
			return (0);
		(close((*fd_in)), close((*fd_out)));
		ft_free_all_malloc();
		free_env(&env);
	}
	else
		return (echo_command2_pipe(node, env, fd_in, fd_out));
	exit (0);
}

void echo_cmd2_pipe_loop(char **arg, int y)
{
	while (arg[y])
	{
		ft_putstr_fd(arg[y], 1);
		if (y < size_of_table(arg) - 1)
			ft_putchar_fd(' ', 1);
		y++;
	}
}

int	echo_command2_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	int	y;
	char	**arg;

	arg = args_to_tab(node->n_value);
	y = 1;
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	if (arg[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		reset_and_close(fd_in, fd_out);
		ft_free_all_malloc();
		free_env(&env);
		close_pipe();
		exit (0);
	}
	echo_cmd2_pipe_loop(arg, y);
	ft_putchar_fd('\n', 1);
	(close((*fd_in)), close((*fd_out)));
	ft_free_all_malloc();
	free_env(&env);
	exit (0);
}
