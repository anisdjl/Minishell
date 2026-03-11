#include "../../minishell.h"

char	*extract_var(t_value_node *n_value, int pos) // le cas $_ et le cas $?
{
	int		i;
	char	*expand_var;

	i = pos;
	while (n_value->value[i] && ft_isalnum(n_value->value[i])) //preparation au malloc
		i++;
	expand_var = ft_malloc(sizeof(char), (i - pos) + 1);
	i = 0;
	while (n_value->value[pos] && ft_isalnum(n_value->value[pos])) // extraction
		expand_var[i++] = n_value->value[pos++];
	return (expand_var);
}

int	predict_expand_size(t_value_node *n_value, t_env *env, int in_squote,
		int in_dquote)
{
	int		i;
	int		size;
	char	*expand;

	i = 0;
	size = 0;
	while (n_value->value[i])
	{
		if (n_value->value[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (n_value->value[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (n_value->value[i] == '$' && !in_squote)
		{
			expand = extract_var(n_value, i + 1);
			printf("expand var : %s\n", expand);
		}
		i++;
	}
}
// addition la taille ce chaque expand trouver

void	expand_loop(t_value_node *n_value, t_env *env, int in_squote,
		int in_dquote)
{
	int		i;
	char	**clean_vers;

	i = 0;
	printf("predict expand size : %i \n", predict_expand_size, n_value, *env,
		in_squote, in_dquote);
}

void	expand(t_value_node *n_value, t_env *env)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
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

// echo "salut $USER"