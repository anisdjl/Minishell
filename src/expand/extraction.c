/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:47:42 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/03 19:50:15 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exp_data(t_expand *exp_data)
{
	exp_data->i = 0;
	exp_data->size = 0;
	exp_data->in_dquote = 0;
	exp_data->in_squote = 0;
}

char	*extract_var(t_value_node *n_value, int pos)
{
	int		i;
	char	*expand_var;

	i = pos;
	while (n_value->value[i] && ft_isalnum(n_value->value[i]))
		i++;
	expand_var = ft_malloc(sizeof(char), (i - pos) + 1);
	i = 0;
	while (n_value->value[pos] && ft_isalnum(n_value->value[pos]))
		expand_var[i++] = n_value->value[pos++];
	expand_var[i] = '\0';
	return (expand_var);
}

char	*extract_env_value(t_value_node *n_value, t_env *env, char *search)
{
	int		i;
	char	*expand;

	(void)n_value;
	i = 1;
	while (env)
	{
		if (ft_strncmp(env->key, search, ft_strlen(search)) == 0
			&& ft_strlen(env->key) == ft_strlen(search))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	expand = ft_malloc(sizeof(char), ft_strlen(env->value) + 1);
	while (env->value[i])
	{
		expand[i - 1] = env->value[i];
		i++;
	}
	expand[i - 1] = '\0';
	return (expand);
}

int	predict_expand_size(t_value_node *n_value, t_env *env)
{
	t_expand	exp_data;

	init_exp_data(&exp_data);
	while (n_value->value[exp_data.i])
	{
		if (n_value->value[exp_data.i] == '\'')
			exp_data.in_squote = !exp_data.in_squote;
		else if (n_value->value[exp_data.i] == '\"')
			exp_data.in_dquote = !exp_data.in_dquote;
		if (n_value->value[exp_data.i] == '$' && !exp_data.in_squote)
		{
			exp_data.expand = extract_var(n_value, exp_data.i + 1);
			exp_data.expand_value = extract_env_value(n_value, env,
					exp_data.expand);
			if (exp_data.expand_value)
			{
				exp_data.size = exp_data.size
					+ ft_strlen(exp_data.expand_value);
				exp_data.i = exp_data.i + ft_strlen(exp_data.expand);
			}
		}
		exp_data.size++;
		exp_data.i++;
	}
	return (exp_data.size + 2);
}
