/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wash_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:48:18 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/02 17:02:02 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wash_machine_loop(t_value_node *n_value, int in_squote, int in_dquote)
{
	int		i;
	int		j;
	char	*wash_version;

	i = 0;
	j = 0;
	wash_version = ft_malloc(sizeof(char), ft_strlen(n_value->value) + 1);
	while (n_value->value[i])
	{
		if (n_value->value[i] == '\'' && in_dquote == 0)
			in_squote = !in_squote;
		else if (n_value->value[i] == '\"' && in_squote == 0)
			in_dquote = !in_dquote;
		else
		{
			wash_version[j] = n_value->value[i];
			j++;
		}
		i++;
	}
	wash_version[j] = '\0';
	n_value->value = wash_version;
}

void	wash_machine(t_value_node *n_value)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
	wash_machine_loop(n_value, in_squote, in_dquote);
}

void	wash_start(t_value_node *n_value)
{
	while (n_value)
	{
		if (n_value)
			wash_machine(n_value);
		n_value = n_value->next;
	}
}
