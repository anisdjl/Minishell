/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butltin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 19:10:46 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/06 11:39:51 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	echo_command_loop(char **arg, int y)
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

int	pwd_command_loop(t_env *tmp, void *ptr, char *current_dir)
{
	if (ptr)
		printf("%s\n", current_dir);
	else if (!ptr)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->key, "PWD", 3) == 0 && ft_strlen(tmp->key) == 3)
			{
				printf("%s\n", tmp->value + 1);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}

void	echo_command2_loop(char **arg, int y)
{
	while (arg[y])
	{
		ft_putstr_fd(arg[y], 1);
		if (y < size_of_table(arg) - 1)
			ft_putchar_fd(' ', 1);
		y++;
	}
}

void	child_exit_status(int status, t_env *env, int pid)
{
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		env->exit_status->exit_status = 128 + WTERMSIG(status);
	}
	if (WIFEXITED(status))
		env->exit_status->exit_status = WEXITSTATUS(status);
}
