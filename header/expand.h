#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_env	t_env;
typedef struct s_tree   t_tree;

void	wash_machine(t_value_node *n_value);
void	wash_start(t_value_node *n_value);
void    wash_machine_loop(t_value_node *n_value, int  in_squote, int  in_dquote);

#endif