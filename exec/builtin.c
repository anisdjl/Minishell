/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:54:04 by anis              #+#    #+#             */
/*   Updated: 2026/03/09 17:23:31 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_command(t_tree *node, t_env *env)
{
	char	current_dir[4096];
	int	fd_in;
	int	fd_out;
	char	**arg;

	arg = args_to_tab(node->n_value);
	save_fds(&fd_in, &fd_out);
	redir_function(node);
	getcwd(current_dir, 4096);
	if (chdir(arg[1]) != 0 || size_of_table(arg) > 2)
	{
		ft_putstr_fd(arg[0], 2);
		write(2, ": ", 2);
		perror(arg[1]);
		reset_and_close(&fd_in, &fd_out);
		return (1);
	}
	reset_and_close(&fd_in, &fd_out);
	return (0);
}

int pwd_command(t_tree *node, t_env *env)
{
	char	current_dir[4096];
	t_env	*tmp;
	void	*ptr;
	int		fd_in;
	int		fd_out;
	
	tmp = env;
	save_fds(&fd_in, &fd_out);
	redir_function(node);
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
	reset_and_close(&fd_in, &fd_out);
	return (0);
}

int	env_command(t_tree *node, t_env **env)
{
	t_env	*tmp;
	int	fd_in;
	int	fd_out;

	if (!env || !*env)
		return (0);
	save_fds(&fd_in, &fd_out);
	redir_function(node);
	tmp = *env;
	while(tmp)
	{
		if (tmp->key && ft_strlen(tmp->key) > 0 && tmp->value && ft_strlen(tmp->value) > 0)
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	reset_and_close(&fd_in, &fd_out);
	return (0);
}


int	echo_command(t_tree *node, t_env *env)
{
	int	y;
	int	fd_in;
	int	fd_out;
	char	**arg;

	arg = args_to_tab(node->n_value);
	if (arg[1] && !check_n(arg[1])) // option -n
	{
		save_fds(&fd_in, &fd_out);
		redir_function(node);
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
		reset_and_close(&fd_in, &fd_out);
	}
	else
		return (echo_command2(node, env));
	return (0);
}

int	echo_command2(t_tree *node, t_env *env)
{
	int	y;
	int	fd_in;
	int	fd_out;
	char	**arg;

	arg = args_to_tab(node->n_value);
	y = 1;
	save_fds(&fd_in, &fd_out);
	redir_function(node);
	if (arg[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (arg[y])
	{
		ft_putstr_fd(arg[y], 1);
		ft_putchar_fd(' ', 1);
		y++;
	}
	ft_putchar_fd('\n', 1);
	reset_and_close(&fd_in, &fd_out);
	return (0);
}
