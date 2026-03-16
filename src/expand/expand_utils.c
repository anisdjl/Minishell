#include "../../minishell.h"

void    expand_$(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	exp_data->expand = ft_strdup("$");
	exp_data->expand_value = ft_strdup("$");
    exp_data->j = 0;
    while (exp_data->expand_value[exp_data->j])
        exp_data->clean_vers[exp_data->k++] = exp_data->expand_value[exp_data->j++];
    exp_data->i = exp_data->i + ft_strlen(exp_data->expand) + 1;
}

void	expand_classic(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
    if (n_value->value[exp_data->i] == '$' && !ft_isalnum(n_value->value[exp_data->i + 1]))
    {
        expand_$(exp_data, n_value, env);
        return;
    }
	exp_data->expand = extract_var(n_value, exp_data->i + 1);
	exp_data->expand_value = extract_env_value(n_value, env, exp_data->expand);
	if (exp_data->expand_value)
	{
		exp_data->j = 0;
		while (exp_data->expand_value[exp_data->j])
			exp_data->clean_vers[exp_data->k++] = exp_data->expand_value[exp_data->j++];
		exp_data->i = exp_data->i + ft_strlen(exp_data->expand) + 1;
	}
	else
	{
		exp_data->i++;
		while (n_value->value[exp_data->i] && ft_isalnum(n_value->value[exp_data->i])) 
			exp_data->i++;
	}
}

void expand_return(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	exp_data->expand = extract_var(n_value, exp_data->i + 1);
	exp_data->expand_value = ft_itoa(env->exit_status->exit_status);
	if (exp_data->expand_value)
	{
		exp_data->j = 0;
		while (exp_data->expand_value[exp_data->j])
			exp_data->clean_vers[exp_data->k++] = exp_data->expand_value[exp_data->j++];
		exp_data->i = exp_data->i + ft_strlen(exp_data->expand) + 1;
	}
	else
	{
        exp_data->i++;
		while (n_value->value[exp_data->i] && ft_isalnum(n_value->value[exp_data->i])) 
			exp_data->i++;
	}
}

void expand_$$(t_expand *exp_data, t_value_node *n_value, t_env *env)
{
	exp_data->expand = extract_var(n_value, exp_data->i + 1);
	exp_data->expand_value = ft_strdup("$");
	if (exp_data->expand_value)
	{
		exp_data->j = 0;
		while (exp_data->expand_value[exp_data->j])
			exp_data->clean_vers[exp_data->k++] = exp_data->expand_value[exp_data->j++];
		exp_data->i = exp_data->i + ft_strlen(exp_data->expand) + 1;
	}
	else
	{
		exp_data->i++;
		while (n_value->value[exp_data->i] && ft_isalnum(n_value->value[exp_data->i])) 
			exp_data->i++;
	}
}