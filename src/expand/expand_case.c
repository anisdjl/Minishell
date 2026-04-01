/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:48:42 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/01 18:00:52 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_dollar(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	exp_data->expand = ft_strdup("$");
	exp_data->expand_value = ft_strdup("$");
	exp_data->j = 0;
	while (exp_data->expand_value[exp_data->j])
	{
		exp_data->clean_vers[exp_data->k++]
			= exp_data->expand_value[exp_data->j++];
	}
	exp_data->i = exp_data->i + ft_strlen(exp_data->expand) + 1;
}

void	expand_return(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	exp_data->expand = NULL;
	exp_data->expand_value = ft_itoa(env->exit_status->exit_status);
	if (exp_data->expand_value)
	{
		exp_data->j = 0;
		while (exp_data->expand_value[exp_data->j])
		{
			exp_data->clean_vers[exp_data->k++]
				= exp_data->expand_value[exp_data->j++];
		}
		exp_data->i = exp_data->i + 2;
	}
	else
	{
		exp_data->i++;
		while (n_value->value[exp_data->i]
			&& ft_isalnum(n_value->value[exp_data->i]))
			exp_data->i++;
	}
}

void	expand_2dollar(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	exp_data->expand = extract_var(n_value, exp_data->i + 1);
	exp_data->expand_value = ft_strdup("$");
	if (exp_data->expand_value)
	{
		exp_data->j = 0;
		while (exp_data->expand_value[exp_data->j])
		{
			exp_data->clean_vers[exp_data->k++]
				= exp_data->expand_value[exp_data->j++];
		}
		exp_data->i = exp_data->i + ft_strlen(exp_data->expand) + 1;
	}
	else
	{
		exp_data->i++;
		while (n_value->value[exp_data->i]
			&& ft_isalnum(n_value->value[exp_data->i]))
			exp_data->i++;
	}
}

int	expand_spe_case(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	if (n_value->value[exp_data->i] == '$' && n_value->value[exp_data->i
			+ 1] != '\0' && n_value->value[exp_data->i + 1] == '$'
		&& !exp_data->in_squote)
	{
		expand_2dollar(exp_data, n_value, env);
		return (1);
	}
	else if (n_value->value[exp_data->i] == '$'
		&& !ft_isalnum(n_value->value[exp_data->i + 1])
		&& n_value->value[exp_data->i + 1] != '\0' && n_value->value[exp_data->i
			+ 1] != '?')
	{
		expand_dollar(exp_data, n_value, env);
		return (1);
	}
	else if (n_value->value[exp_data->i] == '$' && n_value->value[exp_data->i
			+ 1] != '\0' && n_value->value[exp_data->i + 1] == '?'
		&& !exp_data->in_squote)
	{
		expand_return(exp_data, n_value, env);
		return (1);
	}
	return (0);
}

void	do_expand(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	if (expand_spe_case(exp_data, n_value, env))
		return ;
	exp_data->expand = extract_var(n_value, exp_data->i + 1);
	exp_data->expand_value = extract_env_value(n_value, env, exp_data->expand);
	if (exp_data->expand_value)
	{
		if (!exp_data->in_dquote)
			exp_data->expand_value = expand_split(exp_data->expand_value);
		exp_data->j = 0;
		while (exp_data->expand_value[exp_data->j])
		{
			exp_data->clean_vers[exp_data->k++]
				= exp_data->expand_value[exp_data->j++];
		}
		exp_data->i = exp_data->i + ft_strlen(exp_data->expand) + 1;
	}
	else
	{
		exp_data->i++;
		while (n_value->value[exp_data->i]
			&& ft_isalnum(n_value->value[exp_data->i]))
			exp_data->i++;
	}
}
