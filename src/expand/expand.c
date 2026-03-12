#include "../../minishell.h"

void	expand(t_value_node *n_value, t_env *env)
{
	s_expand exp_data;
	
	exp_data.i = 0;
	exp_data.clean_vers = malloc(sizeof(char) * predict_expand_size_size(n_value, env));
	// printf("Size prediction : %i\n", predict_expand_size(n_value, env, in_squote, in_dquote));
	// wash_machine(value);
}

void	domain_expand(t_tree *node, t_env *env)
{
	if (!node || !node->n_value)
		return ;
	while (node->n_value)
	{
		expand(node->n_value, env);
		node->n_value = node->n_value->next;
	}
}
