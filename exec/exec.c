/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:07:42 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/28 15:03:56 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec(t_tree *ast, t_env *env)
{
	if (!ast)
		return (1);
	domain_expand(ast, env);
	if (ast->type == AND)
	{
		env->exit_status->exit_status = exec(ast->left, env);
		if (env->exit_status->exit_status == 0)
			env->exit_status->exit_status = exec(ast->right, env);
		return (env->exit_status->exit_status);
	}
	else if (ast->type == OR)
	{
		env->exit_status->exit_status = exec(ast->left, env);
		if (env->exit_status->exit_status != 0)
			env->exit_status->exit_status=  exec(ast->right, env);
		return (env->exit_status->exit_status);
	}
	else if (ast->type == PIPE)
	{
		handle_pipes(ast, env, 0, 1);
		wait_all_pids(env);//ici le boucle wait all pipes
	}
	else if (ast->type == L_PARENTHESE)
		return (subshell(ast, env));
	else if (ast->type == WORD)
	{
		env->exit_status->exit_status = exec_cmd(ast, env);
		return (env->exit_status->exit_status);
	}
	return (1);
}

int	subshell(t_tree *node, t_env *env)
{
	int	pid_subshell;
	int	status;

	status = 0;
	pid_subshell = fork();
	if (pid_subshell < 0)
	{
		ft_free_all_malloc();
		//free env
		exit(EXIT_FAILURE);
	}
	if (pid_subshell == 0)
	{
		exit(exec(node->left, env));
	}
	waitpid(pid_subshell, &status, 0);
	if (WIFEXITED(status))
		env->exit_status->exit_status = WEXITSTATUS(status);
	return (env->exit_status->exit_status);
}

int	exec_cmd(t_tree *node, t_env *env)
{
	char	**arg;

	// domain_expand(node, env);
	arg = args_to_tab(node->n_value);
	if (arg && arg[0] && ft_strlen(arg[0]) == 4
		&& ft_strncmp(arg[0], "echo", 4) == 0)
		return (echo_command(node, env));
	if (arg && arg[0] && ft_strlen(arg[0]) == 2 
		&& ft_strncmp(arg[0], "cd", 2) == 0)
	 	return (cd_command(node, env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 3
		&& ft_strncmp(arg[0], "pwd", 3) == 0)
		return (pwd_command(node, env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 6
		&& ft_strncmp(arg[0], "export", 6) == 0)
		return (export_cmd(node, &env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 5
		&& ft_strncmp(arg[0], "unset", 5) == 0)
		return (unset_command(node, &env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 3
		&& ft_strncmp(arg[0], "env", 3) == 0)
		return (env_command(node, &env));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 4
		&& ft_strncmp(arg[0], "exit", 4) == 0)
		exit_command(node, env);
	else
		return (exec_normal_command(node, env));
	return (1);
}

int	exec_normal_command(t_tree *node, t_env *env)
{
	int		pid;
	int		status;

	status = 0;
	if ((pid = fork()) < 0)
	{
		ft_free_all_malloc();
		exit(EXIT_FAILURE); // ou affiche juste le prompt
	}
	if (pid == 0) // on est dans le fils
	{
		if (redir_function(node) == 1)
			exit (1);
		child(node, env);
	}
	else if (pid != 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			env->exit_status->exit_status = WEXITSTATUS(status);
		return (env->exit_status->exit_status);
	}
	return(env->exit_status->exit_status);
}

int	child(t_tree *node, t_env *env)
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
	{
		ft_putstr_fd("minsihell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (126);
	}
	if (arg && arg[0] && !given_path(arg[0]))
		path = find_path(arg[0], paths);
	else
		path = ft_strdup(arg[0]);
	execve(path, arg, env_tab);
	(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(arg[0], 2),
	ft_putstr_fd(": permission denied\n", 2));
	ft_free_all_malloc();
	exit (127);
}
