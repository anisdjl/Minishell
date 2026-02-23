#include "../../minishell.h"

void print_ast(t_tree *tree, int depth)
{
    if (!tree)
        return;

    // indentation
    for (int i = 0; i < depth; i++)
        printf("  ");

    // affichage selon le type
    if (tree->type == WORD)
    {
        printf("COMMAND:");
        if (tree->arg)
        {
            for (int i = 0; tree->arg[i]; i++)
                printf(" %s", tree->arg[i]);
        }
        printf("\n");
    }
    else if (tree->type == PIPE)
        printf("PIPE\n");
    else if (tree->type == AND)
        printf("AND\n");
    else if (tree->type == OR)
        printf("OR\n");
    else if (tree->type == RIGHT_A)
        printf("REDIRECT >\n");
    else if (tree->type == LEFT_A)
        printf("REDIRECT <\n");

    // récursion sur les sous-arbres
    print_ast(tree->left, depth + 1);
    print_ast(tree->right, depth + 1);
}

int count_word(t_token *start, t_token *end)
{
	int count;

	count = 0;
	while (start != end)
	{
		start = start->next;
		count++;
	}
	return (count);
}

t_token	*find_op(t_token *start, t_token *end, t_enum type)// On garde le dernier trouver de droite a gauche !
{                                                 // d'ou une variable tmp et pas un return direct sur le premier resultat
	t_token *tmp = start;
	t_token *op = NULL;

	while (tmp != end)
	{
		if (tmp->type == type)
			op = tmp;
		tmp = tmp->next;
	}
	return (op);
}