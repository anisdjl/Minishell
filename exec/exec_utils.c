/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:34:02 by anis              #+#    #+#             */
/*   Updated: 2026/04/04 16:38:53 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

char	**args_to_tab(t_value_node *node_values)
{
	char			**args;
	t_value_node	*tmp;
	int				y;

	if (!node_values)
		return (NULL);
	y = ft_lstsize_arg(node_values);
	tmp = node_values;
	args = ft_malloc(1, sizeof(char *) * (y + 1));
	y = 0;
	while (tmp)
	{
		if (tmp->value[0] != '\0')
		{
			args[y] = ft_strdup(tmp->value);
			y++;
		}
		tmp = tmp->next;
	}
	args[y] = NULL;
	return (args);
}

int	ft_lstsize_arg(t_value_node *node_value)
{
	int	y;

	y = 0;
	while (node_value)
	{
		node_value = node_value->next;
		y++;
	}
	return (y);
}
