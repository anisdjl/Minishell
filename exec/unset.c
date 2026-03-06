/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:05:40 by anis              #+#    #+#             */
/*   Updated: 2026/03/06 12:03:22 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_command(t_tree *node, t_env **env)
{
	t_env	*tmp;
	int		y;
	int	fd_in;
	int	fd_out;

	((y = 1), save_fds(&fd_in, &fd_out));
	redir_function(node);
	if (!env || !*env)
		return (0);
	tmp = *env;
	if (valid_unset(node->arg) == 1)
		return (1);
	while (node->arg[y])
	{
		while (tmp)
		{
			if (ft_strncmp(node->arg[y], tmp->key, ft_strlen(node->arg[y])) == 0)
				unset_node(env, tmp);
			tmp = tmp->next;
		}
		tmp = *env;
		y++;
	}
	reset_and_close(&fd_in, &fd_out);
	return (0);
}

int	valid_unset(char **args)
{
	int	y;
	int	a;

	a = 0;
	y = 1;
	// verfier le args 1
	while (args[y])
	{
		while (args[y][a])
		{
			if (args[y][0] == '\0' || only_spaces(args[y])
				|| (args[y][a] >= '0' && args[y][a] <= '9') || args[y][a] == '-')
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(args[y], 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
				return (1);
			}
			a++;
		}
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
		prev = current; // si il free c'est use after free
		current = current->next;
	}
}
