/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:57 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/06 11:36:44 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	export_update_create(t_tree *node, t_env **env, int y)
{
	char	*key;
	char	**arg;

	arg = args_to_tab(node->n_value);
	key = create_key(arg[y]);
	if (check_existant(*env, key))
	{
		update_env(*env, arg[y], key);
		free(key);
	}
	else
	{
		create_new_node(env, arg[y]);
		free(key);
	}
}

int	export_cmd(t_tree *node, t_env **env)
{
	int		y;
	int		status;
	char	**arg;
	int		fd_in;
	int		fd_out;

	arg = args_to_tab(node->n_value);
	if (!env || !*env)
		return (0);
	(save_fds(&fd_in, &fd_out), status = 0);
	if (arg[1] == NULL)
		return (env_command_for_export(node, env));
	y = 1;
	if (redir_function(node))
		return (1);
	while (arg[y])
	{
		if (valid_export(arg[y]))
			status = 1;
		else
			export_update_create(node, env, y);
		y++;
	}
	reset_and_close(&fd_in, &fd_out);
	return (status);
}

void	update_env(t_env *env, char *arg, char *splitted)
{
	t_env	*tmp;
	void	*ptr;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, splitted, ft_strlen(splitted)) == 0
			&& ft_strlen(tmp->key) == ft_strlen(splitted))
		{
			free(tmp->value);
			ptr = ft_strchr(arg, '=');
			if (ptr)
				tmp->value = ft_strdup_env(ptr);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

void	create_new_node(t_env **env, char *arg)
{
	void	*ptr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ft_free_all_malloc();
		free_env(env);
		exit(EXIT_FAILURE);
	}
	new->next = NULL;
	new->key = create_key(arg);
	ptr = ft_strchr(arg, '=');
	if (ptr)
		new->value = ft_strdup_env(ptr);
	else
		new->value = NULL;
	ft_lstadd_back_env(env, new);
}

int	check_existant(t_env *env, char *key)
{
	t_env	*tmp;

	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == ft_strlen(key)
			&& ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
