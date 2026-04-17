/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:26:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/17 15:48:12 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	char	current_dir[4096];
	char	**arg;

	arg = args_to_tab(node->n_value);
	if (redir_function(node))
		exit (1);
	getcwd(current_dir, 4096);
	if (!arg[1])
		exit (go_to_home_pipe(node, env, current_dir));
	if (size_of_table(arg) > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit (1);
	}
	if (ft_strlen(arg[1]) == 1 && arg[1][0] == '-')
		exit (return_to_old_pwd_pipe(node, env, current_dir));
	if (chdir(arg[1]) != 0)
		exit (error_cd_pipe(arg, fd_in, fd_out));
	extract_oldpwd_pipe(node->n_value, env, current_dir);
	close(*fd_in);
	close(*fd_out);
	ft_free_all_malloc();
	free_env(&env);
	close_pipe();
	exit (0);
}

int	error_cd_pipe(char **arg, int *fd_in, int *fd_out)
{
	ft_putstr_fd(arg[0], 2);
	write(2, ": ", 2);
	perror(arg[1]);
	close(*fd_in);
	close(*fd_out);
	return (1);
}

int	go_to_home_pipe(t_tree *node, t_env *env, char *current_dir)
{
	t_tree	*home;

	home = ft_malloc(1, sizeof(t_tree));
	home->n_value = ft_malloc(1, sizeof(t_value_node));
	home->n_value->value = ft_strdup("$HOME");
	domain_expand(home, env);
	if (chdir(home->n_value->value) != 0)
	{
		ft_putstr_fd("cd", 2);
		write(2, ": ", 2);
		perror(home->n_value->value);
		reset_and_close(&node->fd_in, &node->fd_out);
		return (1);
	}
	reset_and_close(&node->fd_in, &node->fd_out);
	extract_oldpwd(node->n_value, env, current_dir);
	ft_free_all_malloc();
	free_env(&env);
	close_pipe();
	return (0);
}

void	extract_oldpwd_pipe(t_value_node *n_value, t_env *env, char *new_value)
{
	(void)n_value;
	if (!env)
		return ;
	while (env)
	{
		if (ft_strncmp(env->key, "OLDPWD", ft_strlen("OLDPWD")) == 0
			&& ft_strlen(env->key) == ft_strlen("OLDPWD"))
		{
			free(env->value);
			env->value = ft_strjoin_env("=", new_value);
			break ;
		}
		env = env->next;
	}
	return ;
}

int	return_to_old_pwd_pipe(t_tree *node, t_env *env, char *current_dir)
{
	t_tree	*home;

	home = ft_malloc(1, sizeof(t_tree));
	home->n_value = ft_malloc(1, sizeof(t_value_node));
	home->n_value->value = ft_strdup("$OLDPWD");
	domain_expand(home, env);
	if (chdir(home->n_value->value) != 0)
	{
		ft_putstr_fd("cd", 2);
		write(2, ": ", 2);
		perror(home->n_value->value);
		reset_and_close(&node->fd_in, &node->fd_out);
		return (1);
	}
	extract_oldpwd(node->n_value, env, current_dir);
	ft_free_all_malloc();
	free_env(&env);
	close_pipe();
	return (0);
}
