/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:37:48 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/07 16:11:31 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd_cmd_pipe_loop(t_env	*tmp)
{
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 3) == 0 && ft_strlen(tmp->key) == 3)
		{
			printf("%s\n", tmp->value + 1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	pwd_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	char	current_dir[4096];
	t_env	*tmp;
	void	*ptr;

	tmp = env;
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	ptr = getcwd(current_dir, 4096);
	if (ptr)
		printf("%s\n", current_dir);
	else if (!ptr)
	{
		if (!pwd_cmd_pipe_loop(tmp))
			return (0);
	}
	(close((*fd_in)), close((*fd_out)));
	ft_free_all_malloc();
	free_env(&env);
	exit (0);
}
