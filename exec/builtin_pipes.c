/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:45:25 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/28 11:22:05 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cd_command_pipe(t_tree *node, t_env *env, int *fd_in , int *fd_out)
{
	char	current_dir[4096];
	char	**arg;

	wash_start(node->n_value);
	arg = args_to_tab(node->n_value);
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	getcwd(current_dir, 4096);
	if (chdir(arg[1]) != 0 || size_of_table(arg) > 2)
	{
		ft_putstr_fd(arg[0], 2);
		write(2, ": ", 2);
		perror(arg[1]);
		(close((*fd_in)), close((*fd_out)));
		exit (1);
	}
	(close((*fd_in)), close((*fd_out)));
	exit (0);
}

int pwd_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	char	current_dir[4096];
	t_env	*tmp;
	void	*ptr;
	
	tmp = env;
	wash_start(node->n_value);
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	ptr = getcwd(current_dir, 4096);
	if (ptr)
		printf("%s\n", current_dir);
	else if (!ptr)
	{
		while(tmp)
		{
			if (ft_strncmp(tmp->key, "PWD", 3) == 0 && ft_strlen(tmp->key) == 3)
			{
				printf("%s\n", tmp->value + 1);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	(close((*fd_in)), close((*fd_out)));
	exit (0);
}

int	env_command_pipe(t_tree *node, t_env **env, int *fd_in, int *fd_out)
{
	t_env	*tmp;

	if (!env || !*env)
		exit (0);
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	tmp = *env;
	while(tmp)
	{
		if (tmp->key && ft_strlen(tmp->key) > 0 && tmp->value && ft_strlen(tmp->value) > 0)
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	(close((*fd_in)), close((*fd_out)));
	exit (0);
}

int	echo_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	int	y;
	char	**arg;

	wash_start(node->n_value);
	arg = args_to_tab(node->n_value);
	if (arg[1] && !check_n(arg[1])) // option -n
	{
		if (redir_for_pipes(node, fd_in, fd_out))
			exit(1);
		y = 2;
		if (arg[2] == NULL)
			return (0);
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
		(close((*fd_in)), close((*fd_out)));
	}
	else
		return (echo_command2_pipe(node, env, fd_in, fd_out));
	exit (0);
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
		exit (0);
	}
	while (arg[y])
	{
		ft_putstr_fd(arg[y], 1);
		ft_putchar_fd(' ', 1);
		y++;
	}
	ft_putchar_fd('\n', 1);
	(close((*fd_in)), close((*fd_out)));
	exit (0);
}

int	builtin_pipe(t_tree *node, t_env *env , int *fd_in, int *fd_out)
{
	char	**arg;

	if (*fd_in != 0)
		(dup2(*fd_in, 0), close(*fd_in));
	if (*fd_out != 1)
		(dup2(*fd_out, 1), close(*fd_out));
	arg = args_to_tab(node->n_value);
	if (arg && arg[0] && ft_strlen(arg[0]) == 4
		&& ft_strncmp(arg[0], "echo", 4) == 0)
		return (echo_command_pipe(node, env, fd_in, fd_out));
	if (arg && arg[0] && ft_strlen(arg[0]) == 2 
		&& ft_strncmp(arg[0], "cd", 2) == 0)
	 	return (cd_command_pipe(node, env, fd_in , fd_out));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 3
		&& ft_strncmp(arg[0], "pwd", 3) == 0)
		return (pwd_command_pipe(node, env, fd_in, fd_out));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 6
		&& ft_strncmp(arg[0], "export", 6) == 0)
		return (export_pipe(node, &env, fd_in, fd_out));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 5
		&& ft_strncmp(arg[0], "unset", 5) == 0)
		return (unset_command_pipe(node, &env, fd_in, fd_out));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 3
		&& ft_strncmp(arg[0], "env", 3) == 0)
		return (env_command_pipe(node, &env, fd_in, fd_out));
	else if (arg && arg[0] && ft_strlen(arg[0]) == 4
		&& ft_strncmp(arg[0], "exit", 4) == 0)
		exit_command_pipe(node, env, fd_in, fd_out);
	return (44444);
}
