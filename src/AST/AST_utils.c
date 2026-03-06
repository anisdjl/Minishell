#include "../../minishell.h"

void print_ast(t_tree *tree, char *prefix, int is_left)
{
    t_value_node    *v_node;
    t_redir         *r;

    if (!tree) return;
    printf("%s%s", prefix, is_left ? "├── " : "└── ");

    if (tree->type == WORD || tree->type == L_PARENTHESE)
    {
        if (tree->type == WORD) printf("\033[32m[CMD]\033[0m");
        else printf("\033[35m( SUBSHELL )\033[0m");
    
        v_node = tree->n_value;
        while (v_node)
        {
            if (v_node->value)
                printf(" %s", v_node->value);
            v_node = v_node->next;
        }
        r = tree->redirs;
        while (r)
        {
            char *sym = (r->type == LEFT_A) ? "<" : (r->type == RIGHT_A) ? ">" : 
                        (r->type == APPEND) ? ">>" : "<<";
            printf("\n%s%s    \033[90m╰─\033[0m \033[36m%s %s\033[0m", 
                   prefix, is_left ? "│" : " ", sym, r->value);
            r = r->next;
        }
    }
    else if (tree->type == PIPE) printf("\033[33m[PIPE |]\033[0m");
    else if (tree->type == OR)   printf("\033[31m[OR ||]\033[0m");
    else if (tree->type == AND)  printf("\033[34m[AND &&]\033[0m");

    printf("\n");
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "│   " : "    ");
    print_ast(tree->left, new_prefix, 1);
    print_ast(tree->right, new_prefix, 0);
}

void print_redirs(t_redir *redir)
{
    while (redir)
    {
        printf(" [REDIR: type %d -> %s]", redir->type, redir->value);
        redir = redir->next;
    }
}

int	count_word(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	while (start != end)
	{
		start = start->next;
		count++;
	}
	return (count);
}

t_token	*find_op(t_token *start, t_token *end, t_enum type) // On garde le dernier trouver de droite a gauche !
{                                                          
	// d'ou une variable tmp et pas un return direct sur le premier resultat
	int subshell;
	t_token *tmp;
	t_token *op;

	op = NULL;
	tmp = start;
	subshell = 0;
	while (tmp != end)
	{
		if (tmp->type == L_PARENTHESE)
			subshell++;
		else if (tmp->type == R_PARENTHESE)
			subshell--;
		if (subshell == 0 && tmp->type == type)
			op = tmp;
		tmp = tmp->next;
	}
	return (op);
}

t_token	*AST_EVAL_OP(t_token *start, t_token *end)
{
	t_token	*op_pos;

	op_pos = find_op(start, end, OR);
	if (!op_pos)
		op_pos = find_op(start, end, AND);
	if (!op_pos)
		op_pos = find_op(start, end, PIPE);
	return (op_pos);
}

