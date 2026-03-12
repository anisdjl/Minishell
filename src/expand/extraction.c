#include "../../minishell.h"

// addition de la taille sur chaque expand trouver
char	*extract_var(t_value_node *n_value, int pos) // le cas $_ et le cas $? non gere
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

char  *extract_env_var(t_value_node *n_value, t_env *env, char *search)
{
    int i;
    char *expand;

    i = 1;
    while (env)
    {
        if (ft_strncmp(env->key, search, ft_strlen(search)) == 0 && ft_strlen(env->key) == ft_strlen(search))
            break;
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
    expand[i] = '\0';
    return (expand);
}

int	predict_expand_size(t_value_node *n_value, t_env *env)
{
    s_expand exp_data;

	exp_data.i = 0;
    exp_data.size = 0;
	while (n_value->value[exp_data.i])
	{
		if (n_value->value[exp_data.i] == '\'')
			exp_data.in_squote = !exp_data.in_squote;
		else if (n_value->value[exp_data.i] == '\"')
			exp_data.in_dquote = !exp_data.in_dquote;
		if (n_value->value[exp_data.i] == '$' && !exp_data.in_squote)
		{
			exp_data.expand = extract_var(n_value, exp_data.i + 1);
			exp_data.expand_value = extract_env_var(n_value, env, exp_data.expand);
            printf("expand var : %s\n", exp_data.expand);
            if (exp_data.expand_value)
            {
                printf("======== Debug ========\nSize : %i\n", ft_strlen(exp_data.expand_value));
                printf("expand : %s\n=======================\n", exp_data.expand_value);

                exp_data.size = exp_data.size + ft_strlen(exp_data.expand_value);
                exp_data.i = exp_data.i + ft_strlen(exp_data.expand);
            }
		}
        exp_data.size++;
		exp_data.i++;
	}
    return (exp_data.size - 1);
}

