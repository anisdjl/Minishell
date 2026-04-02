/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:39:19 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/02 16:04:47 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_expand(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	int	size;

	size = predict_expand_size(n_value, env);
	exp_data->i = 0;
	exp_data->j = 0;
	exp_data->k = 0;
	exp_data->size = 0;
	exp_data->in_dquote = 0;
	exp_data->in_squote = 0;
	exp_data->clean_vers = ft_malloc(sizeof(char), size);
}

void	expand(t_value_node *n_value, t_env *env)
{
	t_expand	exp_data;

	init_expand(&exp_data, n_value, env);
	while (n_value->value[exp_data.i])
	{
		if (n_value->value[exp_data.i] == '\'')
			exp_data.in_squote = !exp_data.in_squote;
		else if (n_value->value[exp_data.i] == '\"')
			exp_data.in_dquote = !exp_data.in_dquote;
		if (n_value->value[exp_data.i] == '$' && n_value->value[exp_data.i
				+ 1] != '\0' && (exp_data.in_dquote || !exp_data.in_squote))
			do_expand(&exp_data, n_value, env);
		else
			exp_data.clean_vers[exp_data.k++] = n_value->value[exp_data.i++];
	}
	exp_data.clean_vers[exp_data.k] = '\0';
	n_value->value = exp_data.clean_vers;
}

void	domain_expand(t_tree *node, t_env *env)
{
	t_value_node	*tmp;

	tmp = node->n_value;
	if (!tmp || !tmp->value)
		return ;
	while (tmp)
	{
		expand(tmp, env);
		tmp = tmp->next;
	}
}
