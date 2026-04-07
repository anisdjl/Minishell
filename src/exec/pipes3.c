/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:07:51 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 16:39:27 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_pipe(char *path, char **paths, char **env_tab, char **arg)
{
	(void)paths;
	execve(path, arg, env_tab);
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_free_all_malloc();
	exit (127);
}

void	add_pid_to_list(t_env *env, int pid)
{
	t_pid	*pid_new;

	pid_new = ft_lstnew_pid(pid);
	ft_lstadd_back_pid(&env->pid, pid_new);
}

int	wait_all_pids(t_env *env)
{
	t_pid	*tmp;
	int		status;

	status = 0;
	tmp = env->pid;
	while (tmp->next)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	waitpid(tmp->pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status->exit_status = WEXITSTATUS(status);
	return (env->exit_status->exit_status);
}

t_pid	*ft_lstnew_pid(int content)
{
	t_pid	*new_node;

	new_node = malloc(sizeof(t_pid));
	if (!new_node)
		return (NULL);
	new_node->pid = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_pid(t_pid **lst, t_pid *new)
{
	t_pid	*ptr;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		ptr = *lst;
		while (ptr->next)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}
