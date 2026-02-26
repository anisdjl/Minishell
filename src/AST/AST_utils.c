#include "../../minishell.h"

void print_ast(t_tree *tree, char *prefix, int is_left)
{
    if (!tree)
        return;

    // Affichage du préfixe pour dessiner les branches
    printf("%s", prefix);
    printf(is_left ? "├── " : "└── ");

    // Affichage selon ton enum s_enum
    if (tree->type == WORD)
    {
        printf("\033[32m[CMD]\033[0m"); // Vert
        if (tree->arg)
        {
            for (int i = 0; tree->arg[i]; i++)
                printf(" %s", tree->arg[i]);
        }
    }
    else if (tree->type == PIPE)         printf("\033[33m[PIPE |]\033[0m");    // Jaune
    else if (tree->type == OR)           printf("\033[31m[OR ||]\033[0m");     // Rouge
    else if (tree->type == AND)          printf("\033[34m[AND &&]\033[0m");    // Bleu
    else if (tree->type == HERE_DOC)     printf("\033[36m[HEREDOC <<]\033[0m"); // Cyan
    else if (tree->type == RIGHT_A)      printf("\033[36m[REDIR >]\033[0m");    // Cyan
    else if (tree->type == LEFT_A)       printf("\033[36m[REDIR <]\033[0m");    // Cyan
    else if (tree->type == APPEND)       printf("\033[36m[APPEND >>]\033[0m");  // Cyan
    else if (tree->type == SUBSHELL || tree->type == L_PARENTHESE) 
                                         printf("\033[35m( SUBSHELL )\033[0m"); // Magenta
    else printf("TYPE: %u", tree->type);
    
    printf("\n");

    // Préparation du préfixe pour les lignes verticales des enfants
    char new_prefix[256];
    sprintf(new_prefix, "%s%s", prefix, is_left ? "│   " : "    ");

    // Récursion : Gauche (is_left = 1) puis Droite (is_left = 0)
    if (tree->left || tree->right)
    {
        print_ast(tree->left, new_prefix, 1);
        print_ast(tree->right, new_prefix, 0);
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
