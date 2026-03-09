/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:57 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/09 17:14:08 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	export(t_tree *node, t_env **env)
{
	int	y;
	int		status;
	char	**arg;

	arg = args_to_tab(node->n_value);
	if (!env || !*env)
		return (0);
	status = 0;
	if (arg[1] == NULL)
		return (env_command_for_export(node, env));
	y = 1;
	while (arg[y])
	{
		if (valid_export(arg[y]))
			status = 1;
		else
			export_update_create(node, env, y);
		y++;
	}
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
		exit(EXIT_FAILURE); // + free env
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
		if (ft_strlen(tmp->key) == ft_strlen(key) && ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	valid_export(char *args)
{
	int	y;

	y = 0;
	if (args[0] == '\0' || only_spaces(args) || (!((args[0] >= 'a' && args[0] <= 'z') 
        || (args[0] >= 'A' && args[0] <= 'Z') 
        || (args[0] == '_'))))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);	
		return (1);
	}
	while (args[++y] && args[y] != '=')
	{
		if (!ft_isalnum(args[y]) && args[y] != '_')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);	
			return (1);
		}
	}
	return (0);
}
