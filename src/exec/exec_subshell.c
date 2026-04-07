/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:12:00 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/07 16:10:41 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	subshell_exit(t_env *env)
{
	ft_free_all_malloc();
	free_env(&env);
	exit(EXIT_FAILURE);
}

int	subshell(t_tree *node, t_env *env)
{
	int	pid_subshell;
	int	status;

	status = 0;
	pid_subshell = fork();
	if (pid_subshell < 0)
		subshell_exit(env);
	if (pid_subshell == 0)
	{
		if (redir_function(node) == 1)
		{
			free_env(&env);
			exit(1);
		}
		status = exec(node->left, &env);
		free_env(&env);
		ft_free_all_malloc();
		close_pipe();
		exit(status);
	}
	waitpid(pid_subshell, &status, 0);
	if (WIFEXITED(status))
		env->exit_status->exit_status = WEXITSTATUS(status);
	return (env->exit_status->exit_status);
}
