/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:29:52 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/08 17:11:32 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_pipe_subshell(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		ft_free_all_malloc();
		free_env(&env);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exec_pipe_subshell2(node, env, &fd_in, &fd_out);
		status = exec(node->left, &env);
		free_env(&env);
		ft_free_all_malloc();
		close_pipe();
		exit (status);
	}
	return (pid);
}

void	close_pipe(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		if (fd != STDERR_FILENO && fd != STDIN_FILENO && fd != STDOUT_FILENO)
			close (fd);
		fd++;
	}
}

void	handle_pipes(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	fd[2];
	int	pid;

	if (node->type == PIPE)
	{
		if (pipe(fd) < 0)
			exit_wrong_pid(env);
		handle_pipes(node->left, env, fd_in, fd[1]);
		close(fd[1]);
		if (fd_in != 0)
			close(fd_in);
		handle_pipes(node->right, env, fd[0], fd_out);
		close(fd[0]);
	}
	else if (node->type == WORD)
	{
		pid = exec_pipe_cmd(node, env, fd_in, fd_out);
		add_pid_to_list(env, pid);
	}
	else if (node->type == L_PARENTHESE)
	{
		pid = exec_pipe_subshell(node, env, fd_in, fd_out);
		add_pid_to_list(env, pid);
	}
}

int	exec_pipe_cmd(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	pid;

	if (!node->n_value)
		return (0);
	domain_expand(node, env);
	pid = fork();
	if (pid < 0)
	{
		ft_free_all_malloc();
		free_env(&env);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close_extra_fds(node, fd_in, fd_out);
		check_empty_redirs(node, env, &fd_in, &fd_out);
		if (builtin_pipe(node, env, &fd_in, &fd_out) == 44444)
			child_pipe(node, env, fd_in, fd_out);
		else
			exit(env->exit_status->exit_status);
	}
	return (pid);
}

void	child_pipe(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	char	*path;
	char	**paths;
	char	**env_tab;
	char	**arg;

	wash_start(node->n_value);
	arg = args_to_tab(node->n_value);
	env_tab = env_to_tab(&env);
	paths = get_paths(env_tab);
	if (arg && arg[0] && (only_spaces(arg[0]) || arg[0][0] == '\0'))
		exit_void_args(env, arg);
	if (arg && arg[0] && !given_path(arg[0]))
		path = find_path(arg[0], paths, &env);
	else
		path = ft_strdup(arg[0]);
	if (fd_in != STDIN_FILENO)
		(dup2(fd_in, 0), close(fd_in));
	if (fd_out != STDOUT_FILENO)
		(dup2(fd_out, 1), close(fd_out));
	exec_pipe(path, env, env_tab, arg);
}
