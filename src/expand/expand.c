#include "../../minishell.h"

int do_expand(char *s)
{
	int i;

	i = 0;
}
void claim_expand(char *s, t_env *env)
{
	int i;
    char *claim_var;

	i = 0;
	while (s[i] && s[i] > 32)
		i++;
	claim_var = ft_malloc(sizeof(char), i + 1);
	i = 0;
	while (claim_var[i])
	{
		claim_var[i] = s[i];
		i++;
	}
}

void expand(t_tree *node, t_env *env)
{
    while (node->n_value->next)
    {
        if (node->data->flag & F_DQUOTE || node->data->flag == 0)
		{
			if (ft_strchr(node->data->value, '$'))
				claim_expand(ft_strchr(node->data->value, '$'), env);
		}
        else if (node->data->flag & F_SQUOTE)
		{
			printf("Changement d'approche");
		}
        else 
			break;
        node = node->n_value->next;
    }
}
// echo "salut "