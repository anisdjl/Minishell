/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pipes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:50:41 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/04 18:18:06 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	unset_command_pipe(t_tree *node, t_env **env, int *fd_in, int *fd_out)
{
	int		y;
	char	**arg;

	arg = args_to_tab(node->n_value);
	y = 1;
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	if (!env || !*env)
	{
		(close((*fd_in)), close((*fd_out)));
		exit(0);
	}
	while (arg[y])
	{
		unset_node(env, arg[y]);
		y++;
	}
	(close((*fd_in)), close((*fd_out)));
	ft_free_all_malloc();
	free_env(env);
	exit (0);
}

int	export_pipe(t_tree *node, t_env **env, int *fd_in, int *fd_out)
{
	int		y;
	int		status;
	char	**arg;

	wash_start(node->n_value);
	arg = args_to_tab(node->n_value);
	if (!env || !*env)
		exit (0);
	status = 0;
	if (arg[1] == NULL)
		return (env_command_for_export_pipe(node, env, fd_in, fd_out));
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	y = 1;
	while (arg[y])
	{
		if (valid_export(arg[y]))
			status = 1;
		else
			export_update_create(node, env, y);
		y++;
	}
	(close((*fd_in)), close((*fd_out)));
	ft_free_all_malloc();
	free_env(env);
	exit (status);
}

int	env_command_for_export_pipe(t_tree *node,
	t_env **env, int *fd_in, int *fd_out)
{
	t_env	*tmp;

	if (!env || !*env)
		exit (0);
	if (redir_for_pipes(node, fd_in, fd_out))
		exit (1);
	tmp = *env;
	while (tmp)
	{
		if (tmp->key && ft_strlen(tmp->key)
			> 0 && tmp->value && ft_strlen(tmp->value) > 0)
			printf("export %s%s\n", tmp->key, tmp->value);
		else
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
	(close((*fd_in)), close((*fd_out)));
	ft_free_all_malloc();
	free_env(env);
	exit (0);
}
