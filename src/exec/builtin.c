/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:54:04 by anis              #+#    #+#             */
/*   Updated: 2026/04/08 17:09:19 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd_command(t_tree *node, t_env *env)
{
	char	current_dir[4096];
	t_env	*tmp;
	void	*ptr;
	int		fd_in;
	int		fd_out;

	tmp = env;
	save_fds(&fd_in, &fd_out);
	if (redir_function(node))
	{
		reset_and_close(&fd_in, &fd_out);
		return (1);
	}
	ptr = getcwd(current_dir, 4096);
	if (!pwd_command_loop(tmp, ptr, current_dir))
		return (0);
	reset_and_close(&fd_in, &fd_out);
	return (0);
}

int	env_command(t_tree *node, t_env **env)
{
	t_env	*tmp;
	int		fd_in;
	int		fd_out;

	if (!env || !*env)
		return (0);
	save_fds(&fd_in, &fd_out);
	if (redir_function(node))
	{
		reset_and_close(&fd_in, &fd_out);
		return (1);
	}
	tmp = *env;
	while (tmp)
	{
		if (tmp->key && ft_strlen(tmp->key) > 0 && tmp->value
			&& ft_strlen(tmp->value) > 0)
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	reset_and_close(&fd_in, &fd_out);
	return (0);
}

int	echo_command(t_tree *node, t_env *env)
{
	int		y;
	int		fd_in;
	int		fd_out;
	char	**arg;

	arg = args_to_tab(node->n_value);
	if (arg[1] && !check_n(arg[1]))
	{
		save_fds(&fd_in, &fd_out);
		if (redir_function(node))
		{
			reset_and_close(&fd_in, &fd_out);
			return (1);
		}
		y = 2;
		if (arg[2] == NULL)
			return (0);
		if (!echo_command_loop(arg, y))
			return (0);
		reset_and_close(&fd_in, &fd_out);
	}
	else
		return (echo_command2(node, env));
	return (0);
}

int	echo_command2(t_tree *node, t_env *env)
{
	int		y;
	int		fd_in;
	int		fd_out;
	char	**arg;

	(void)env;
	arg = args_to_tab(node->n_value);
	y = 1;
	save_fds(&fd_in, &fd_out);
	if (redir_function(node))
	{
		reset_and_close(&fd_in, &fd_out);
		return (1);
	}
	if (arg[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		reset_and_close(&fd_in, &fd_out);
		return (0);
	}
	echo_command2_loop(arg, y);
	ft_putchar_fd('\n', 1);
	reset_and_close(&fd_in, &fd_out);
	return (0);
}

void	error_execve(char **arg, char *path, t_env *env)
{
	struct stat	st;

	if (path && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		ft_free_all_malloc();
		free_env(&env);
		exit(126);
	}
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		ft_free_all_malloc();
		free_env(&env);
		exit(126);
	}
	free_env(&env);
	error_execve2(arg);
}
