#include "../../minishell.h"

void	wash_machine(t_value_node *n_value)
{
	int i;
	int j;
	char *wash_version;
	int	 in_squote;
	int	 in_dquote;

	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	wash_version = ft_malloc(sizeof(char), ft_strlen(n_value->value) + 1);
	while (n_value->value[i])
	{
		if (n_value->value[i] == '\'' && in_dquote == 0)
			(in_squote = !in_squote, i++);
		else if (n_value->value[i] == '\"' && in_squote == 0)
			(in_dquote = !in_dquote, i++);
		else
			wash_version[j] = n_value->value[i];
		i++;
		j++;
	}
	wash_version[j] = '\0';
	n_value->value = wash_version;
}

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