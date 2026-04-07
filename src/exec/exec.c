/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:07:42 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 16:10:53 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_next(t_tree *ast, t_env **env)
{
	if (ast->type == PIPE)
	{
		handle_pipes(ast, *env, 0, 1);
		wait_all_pids(*env);
	}
	else if (ast->type == L_PARENTHESE)
		return (subshell(ast, *env));
	else if (ast->type == WORD)
	{
		(*env)->exit_status->exit_status = exec_cmd(ast, env);
		return ((*env)->exit_status->exit_status);
	}
	return (1);
}

int	exec(t_tree *ast, t_env **env)
{
	if (!ast)
		return (0);
	if (ast->type == AND)
	{
		(*env)->exit_status->exit_status = exec(ast->left, env);
		if ((*env)->exit_status->exit_status == 0)
			(*env)->exit_status->exit_status = exec(ast->right, env);
		return ((*env)->exit_status->exit_status);
	}
	else if (ast->type == OR)
	{
		(*env)->exit_status->exit_status = exec(ast->left, env);
		if ((*env)->exit_status->exit_status != 0)
			(*env)->exit_status->exit_status = exec(ast->right, env);
		return ((*env)->exit_status->exit_status);
	}
	return (exec_next(ast, env));
}

int	exec_cmd_next(t_tree *node, t_env **env, char **arg)
{
	arg = args_to_tab(node->n_value);
	if (arg && arg[0] && ft_strlen(arg[0]) == 4
		&& ft_strncmp(arg[0], "echo", 4) == 0)
		return (echo_command(node, *env));
	if (arg && arg[0] && ft_strlen(arg[0]) == 2
		&& ft_strncmp(arg[0], "cd", 2) == 0)
		return (cd_command(node, *env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 3
		&& ft_strncmp(arg[0], "pwd", 3) == 0)
		return (pwd_command(node, *env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 6
		&& ft_strncmp(arg[0], "export", 6) == 0)
		return (export_cmd(node, env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 5
		&& ft_strncmp(arg[0], "unset", 5) == 0)
		return (unset_command(node, env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 3
		&& ft_strncmp(arg[0], "env", 3) == 0)
		return (env_command(node, env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 4
		&& ft_strncmp(arg[0], "exit", 4) == 0)
		exit_command(node, *env);
	else
		return (exec_normal_command(node, *env));
	return (1);
}

int	exec_cmd(t_tree *node, t_env **env)
{
	char	**arg;
	int		fd_in;
	int		fd_out;
	int		status;

	arg = NULL;
	domain_expand(node, *env);
	wash_start(node->n_value);
	if (command_is_empty(node))
	{
		if (node->redirs)
		{
			save_fds(&fd_in, &fd_out);
			status = redir_function(node);
			reset_and_close(&fd_in, &fd_out);
			if (status != 0)
			{
				(*env)->exit_status->exit_status = 1;
				return (1);
			}
		}
		(*env)->exit_status->exit_status = 0;
		return (0);
	}
	return (exec_cmd_next(node, env, arg));
}

int	exec_normal_command(t_tree *node, t_env *env)
{
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_free_all_malloc();
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (redir_function(node) == 1)
		{
			free_env(&env);
			exit (1);
		}
		child(node, env);
	}
	else if (pid != 0)
		child_exit_status(status, env, pid);
	return (env->exit_status->exit_status);
}
