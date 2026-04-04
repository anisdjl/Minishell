/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:21:17 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/04 15:36:42 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cd_command(t_tree *node, t_env *env)
{
	char	current_dir[4096];
	char	**arg;

	arg = args_to_tab(node->n_value);
	save_fds(&node->fd_in, &node->fd_out);
	if (redir_function(node))
	{
		reset_and_close(&node->fd_in, &node->fd_out);
		return (1);
	}
	getcwd(current_dir, 4096);
	if (!arg[1])
		return (go_to_home(node, env, current_dir));
	if (size_of_table(arg) > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	if (ft_strlen(arg[1]) == 1 && arg[1][0] == '-')
		return (return_to_old_pwd(node, env, current_dir));
	if (chdir(arg[1]) != 0)
	{
		ft_putstr_fd(arg[0], 2);
		write(2, ": ", 2);
		perror(arg[1]);
		reset_and_close(&node->fd_in, &node->fd_out);
		return (1);
	}
	extract_oldpwd(node->n_value, env, current_dir);
	reset_and_close(&node->fd_in, &node->fd_out);
	return (0);
}	

int	go_to_home(t_tree *node, t_env *env, char *current_dir)
{
	t_tree *home;
	
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
	return (0);
}

void	extract_oldpwd(t_value_node *n_value, t_env *env, char *new_value)
{
    char *expand;

	expand = NULL;
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

int	return_to_old_pwd(t_tree *node, t_env *env, char *current_dir)
{
	t_tree *home;
	
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
	return (0);
}
