#include "../../minishell.h"

void expand(t_value_node *value, t_env *env)
{
	wash_machine(value);
}

void domain_expand(t_tree *node, t_env *env)
{
	if (!node || !node->n_value)
		return ;
	while (node->n_value)
	{
		expand(node->n_value, env);
		node->n_value =  node->n_value->next;
	}
}
// echo "salut "