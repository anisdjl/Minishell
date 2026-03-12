#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_env	t_env;
typedef struct s_tree	t_tree;

typedef struct t_expand
{
	int		i;
    int     size;
    int     in_squote;
    int     in_dquote;
    char    *expand;
    char    *expand_value;
    char	**clean_vers;
}   s_expand;

void					wash_machine(t_value_node *n_value);
void					wash_start(t_value_node *n_value);
void					domain_expand(t_tree *node, t_env *env);
int						predict_expand_size(t_value_node *n_value, t_env *env);

#endif


// int	predict_expand_size(t_value_node *n_value, t_env *env, int in_squote,
// 		int in_dquote)
// {
//     s_predict predict;

// 	predict.i = 0;
//     predict.size = 0;
// 	printf("predict size launch ! \n");
// 	while (n_value->value[predict.i])
// 	{
// 		if (n_value->value[predict.i] == '\'')
// 			in_squote = !in_squote;
// 		else if (n_value->value[predict.i] == '\"')
// 			in_dquote = !in_dquote;
// 		if (n_value->value[predict.i] == '$' && !in_squote)
// 		{
// 			predict.expand = extract_var(n_value, predict.i + 1);
// 			// printf("expand var : %s\n", expand); // debug
// 			predict.expand_value = extract_env_var(n_value, env, predict.expand);
//             if (predict.expand_value)
//             {
//                 // printf("======== Debug ========\nSize : %i\n", ft_strlen(expand_value));
//                 // printf("expand : %s\n=======================\n", expand_value); // debug
//                 predict.size = predict.size + ft_strlen(predict.expand_value);
//                 i = i + ft_strlen(predict.expand);
//             }
// 		}
//         predict.size++;
// 		predict.i++;
// 	}
//     return (predict.size - 1);
// }