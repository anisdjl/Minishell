#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_env	t_env;
typedef struct s_tree	t_tree;

typedef struct s_expand
{
	int					i;
	int					j;
	int					k;
	int					size;
	int					in_squote;
	int					in_dquote;
	char				*expand;
	char				*expand_value;
	char				*clean_vers;
}						t_expand;

/* Wash quote */

void					wash_machine(t_value_node *n_value);
void					wash_start(t_value_node *n_value);

/* Extraction */

char					*extract_var(t_value_node *n_value, int pos);
char					*extract_env_value(t_value_node *n_value, t_env *env,
							char *search);

/* Expand main */

void					domain_expand(t_tree *node, t_env *env);
int						predict_expand_size(t_value_node *n_value, t_env *env);
void					do_expand(t_expand *exp_data, t_value_node *n_value,
							t_env *env);
void					expand_return(t_expand *exp_data, t_value_node *n_value,
							t_env *env);
void 					expand_2dollar(t_expand *exp_data, t_value_node *n_value, t_env *env);
char					*expand_split(char *expand_value);

#endif
