/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:07:42 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/28 22:34:19 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec(t_tree *ast, t_env *env)
{
	int	status;
	
	status = 0;
	if (ast->type == AND)
	{
		status = exec(ast->left, env);
		if (status == 0)
			return (exec(ast->right, env));
		return (status);
	}
	else if (ast->type == OR)
	{
		status = exec(ast->left, env);
		if (status != 0)
			return (exec(ast->right, env));
		return (status);
	}
	else if (ast->type == PIPE)
		return (handle_pipes(ast, env));
	else if (ast->type == WORD)
		return (exec_cmd(ast, env));
	return (1);
}

int	handle_pipes(t_tree *node, t_env *env) // je ne vois pas comment faire pour l'instant
{
	int	*nb_of_pipes;

	if (node->left->type == PIPE)
		exec(node->left, env);
	else
	{
		if (built_in_cmd(node->left))
			return (exec_built_in(node));
		else
			ft_execve(node);
	}
}

int	exec_cmd(t_tree *node, t_env *env)
{
	if (ft_strlen(node->arg[0]) == 4
		&& ft_strncmp(node->arg[0], "echo", 4) == 0)
		echo_command(node, env);
	else if (ft_strlen(node->arg[0]) == 2 
	&& ft_strncmp(node->arg[0], "cd", 2) == 0)
		cd_command(node, env);
	else if (ft_streln(node->arg[0]) == 3
		&& ft_strncmp(node->arg[0], "pwd", 3) == 0)
		pwd_command(node, env);
	else if (ft_strlen(node->arg[0]) == 6
		&& ft_strcmp(node->arg[0], "export", 6) == 0)
		export_command(node, env);
	else if (ft_strlen(node->arg[0]) == 5
		&& ft_strncmp(node->arg[0], "unset", 5))
		unset_command(node, env);
	else if (ft_strlen(node->arg[0]) == 3
		&& ft_strncmp(node->arg[0], "env", 3))
		env_command(node, env);
	else if (ft_strlen(node->arg[0]) == 4
		&& ft_strncmp(node->arg[0], "exit", 4))
		exit_command(node, env);
	else
		exec_normal_command(node, env);
}

char **env_to_tab(t_env **env)
{
	t_env	*tmp;
	char	**env_tab;
	int		y;

	if (!env || !*env)
		return (NULL);
	y = 0;
	tmp = (*env);
	env_tab = ft_malloc(1, sizeof(char *) * ft_lstsize_env(env) + 1);
	while (tmp)
	{
		env_tab[y] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (env_tab);
}

int	ft_lstsize_env(t_env *lst)
{
	int	y;

	y = 0;
	while (lst)
	{
		lst = lst->next;
		y++;
	}
	return (y);
}
