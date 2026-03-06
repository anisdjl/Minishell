/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:34:02 by anis              #+#    #+#             */
/*   Updated: 2026/03/06 15:46:30 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char **env_to_tab(t_env **env)
{
	t_env	*tmp;
	char	**env_tab;
	int		y;

	if (!env || !*env)
		return (NULL);
	y = 0;
	tmp = (*env);
	env_tab = ft_malloc(1, sizeof(char *) * ft_lstsize_env(*env) + 1);
	while (tmp)
	{
		env_tab[y] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
		y++;
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

int	size_of_table(char **tab)
{
	int	y;

	y = 1;
	if (!tab || !*tab)
		return (0);
	while (tab[y])
		y++;
	return (y);
}

int	check_n(char *args)
{
	int	y;

	y = 0;
	if (args[0] != '-')
		return (1);
	else
		y++;
	while (args[y])
	{
		if (args[y] != 'n')
			return (1);
		y++;
	}
	return (0);
}

void	save_fds(int *fd_in, int *fd_out)
{
	*fd_in = dup(0);
	*fd_out = dup(1);
}

void	reset_and_close(int *fd_in, int *fd_out)
{
	dup2(*fd_in, 0);
	dup2(*fd_out, 1);
	close(*fd_in);
	close(*fd_out);
}
