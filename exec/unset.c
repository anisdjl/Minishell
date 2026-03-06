/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:05:40 by anis              #+#    #+#             */
/*   Updated: 2026/03/06 17:10:59 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_command(t_tree *node, t_env **env)
{
	int		y;
	int		fd_in;
	int		fd_out;

	((y = 1), save_fds(&fd_in, &fd_out));
	redir_function(node);
	if (!env || !*env)
		return (reset_and_close(&fd_in, &fd_out), 0);
	while (node->arg[y])
	{
		unset_node(env, node->arg[y]);
		y++;
	}
	reset_and_close(&fd_in, &fd_out);
	return (0);
}

void	unset_node(t_env **env, char *arg)
{
	t_env	*current;
	t_env	*prev;

	current = (*env);
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, arg, ft_strlen(arg)) == 0
			&& ft_strlen(current->key) == ft_strlen(arg))
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
