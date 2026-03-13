#include "../../minishell.h"

void init_expand(s_expand *exp_data, t_value_node *n_value, t_env *env)
{
	int size;

	size = predict_expand_size(n_value, env);
	exp_data->i = 0;
    exp_data->size = 0;
    exp_data->in_dquote = 0;
    exp_data->in_squote = 0;
	exp_data->clean_vers = malloc(sizeof(char) * size + 1);
	// printf("taille alloue : %i\n", size);
}

void 	expand(t_value_node *n_value, t_env *env)
{
	int j;
	int k;
	s_expand exp_data;

	k = 0;
	init_expand(&exp_data, n_value, env);
	while (n_value->value[exp_data.i])
	{
		if (n_value->value[exp_data.i] == '\'')
			exp_data.in_squote = !exp_data.in_squote;
		else if (n_value->value[exp_data.i] == '\"')
			exp_data.in_dquote = !exp_data.in_dquote;

		if (n_value->value[exp_data.i] == '$' && !exp_data.in_squote)
		{
			exp_data.expand = extract_var(n_value, exp_data.i + 1);
			exp_data.expand_value = extract_env_value(n_value, env, exp_data.expand);
            if (exp_data.expand_value)
            {
				j = 0;
				while (exp_data.expand_value[j])
					exp_data.clean_vers[k++] = exp_data.expand_value[j++];
				exp_data.i = exp_data.i + ft_strlen(exp_data.expand) + 1;
            }
		}
		else
			exp_data.clean_vers[k++] = n_value->value[exp_data.i++];
	}
	exp_data.clean_vers[k] = '\0';
	n_value->value = exp_data.clean_vers;
	wash_machine(n_value);
}

void	domain_expand(t_tree *node, t_env *env)
{
	if (!node || !node->n_value)
		return ;
	while (node->n_value)
	{
		expand(node->n_value, env);
		printf("Value : %s\n", node->n_value->value);
		node->n_value = node->n_value->next;
	}
}
