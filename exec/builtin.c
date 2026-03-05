/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:54:04 by anis              #+#    #+#             */
/*   Updated: 2026/03/05 17:20:23 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_command(t_tree *node, t_env *env)
{
	char	current_dir[4096];
	int	fd_in;
	int	fd_out;

	save_fds(&fd_in, &fd_out);
	redir_function(node);
	getcwd(current_dir, 4096);
	if (size_of_table(node->arg) > 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->arg[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		(dup2(fd_in, 0), dup2(fd_out, 1));
		(close(fd_in), close(fd_out));
		return (1);
	}
	if (chdir(node->arg[1]) != 0)
	{
		ft_putstr_fd(node->arg[0], 2);
		write(2, ": ", 2);
		perror(node->arg[1]);
		(dup2(fd_in, 0), dup2(fd_out, 1));
		(close(fd_in), close(fd_out));
		return (1);
	}
	(dup2(fd_in, 0), dup2(fd_out, 1));
	(close(fd_in), close(fd_out));
	return (0);
}

int pwd_command(t_tree *node, t_env *env)
{
	char	current_dir[4096];
	t_env	*tmp;
	void	*ptr;
	int	fd_in;
	int	fd_out;
	
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
	(dup2(fd_in, 0), dup2(fd_out, 1));
	(close(fd_in), close(fd_out));
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
		if (ft_strlen(tmp->key) > 0 && ft_strlen(tmp->value) > 0)
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	(dup2(fd_in, 0), dup2(fd_out, 1));
	(close(fd_in), close(fd_out));
	return (0);
}


int	echo_command(t_tree *node, t_env *env)
{
	int	y;
	int	fd_in;
	int	fd_out;

	if (node->arg[1] && !check_n(node->arg[1])) // option -n
	{
		save_fds(&fd_in, &fd_out);
		redir_function(node);
		y = 2;
		if (node->arg[2] == NULL)
			return (0);
		while (node->arg[y] && !check_n(node->arg[y]))
			y++;
		if (y == size_of_table(node->arg))
			return (0);
		while (node->arg[y])
		{
			ft_putstr_fd(node->arg[y], 1);
			if (y < size_of_table(node->arg) - 1)
				ft_putchar_fd(' ', 1);
			y++;
		}
		(dup2(fd_in, 0), dup2(fd_out, 1));
		(close(fd_in), close(fd_out));
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

	y = 1;
	save_fds(&fd_in, &fd_out);
	redir_function(node);
	if (node->arg[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (node->arg[y])
	{
		ft_putstr_fd(node->arg[y], 1);
		ft_putchar_fd(' ', 1);
		y++;
	}
	ft_putchar_fd('\n', 1);
	(dup2(fd_in, 0), dup2(fd_out, 1));
	(close(fd_in), close(fd_out));
	return (0);
}

int	unset_command(t_tree *node, t_env **env)
{
	t_env	*tmp;
	int		y;
	int	fd_in;
	int	fd_out;

	y = 1;
	save_fds(&fd_in, &fd_out);
	redir_function(node);
	if (!env || !*env)
		return (0);
	tmp = *env;
	while (node->arg[y])
	{
		if (valid_unset(node->arg[y]))
			printf("%s: not a valid identifier\n", node->arg[y]);
		else
		{
			while (tmp)
			{
				if (!ft_strncmp(node->arg[y], tmp->key, ft_strlen(node->arg[y])))
				{
					unset_node(env, tmp);
				}
				tmp = tmp->next;
			}
		}
		y++;
	}
	(dup2(fd_in, 0), dup2(fd_out, 1));
	(close(fd_in), close(fd_out));
	return (0);
}

int	valid_unset(char *args) // no int no empty param no -
{
	int	y;

	y = 0;
	if (args[0] == '\0' || only_spaces(args))
		return (1);
	while (args[y])
	{
		if ((args[y] >= '0' && args[y] <= '9') || args[y] == '-')
			return (1);
		y++;
	}
	return (0);
}

void	unset_node(t_env **env, t_env *ptr)
{
	t_env	*current;
	t_env	*prev;

	current = (*env);
	prev = NULL;
	while (current)
	{
		if (current == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current);
		}
		prev = current;
		current = current->next;
	}
}
