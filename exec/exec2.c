/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:34:02 by anis              #+#    #+#             */
/*   Updated: 2026/03/04 10:58:35 by adjelili         ###   ########.fr       */
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

	y = 0;
	if (!tab || !*tab)
		return (0);
	while (tab[y])
		y++;
	return (y);
}
