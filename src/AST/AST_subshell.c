#include "../../minishell.h"

t_token	*AST_find_subparent(t_token *start)
{
	int		count;

	count = 1;
    if (!start || start->type != L_PARENTHESE)
        return (NULL);
	start = start->next;
	while (start)
	{
		if (start->type == L_PARENTHESE)
			count++;
		if (start->type == R_PARENTHESE)
			count--;
		if (count == 0)
			return (start);
		start = start->next;
	}
	return (NULL);
}

t_tree	*AST_build_subshell(t_token *start, t_token *end)
{
	t_tree	*node;
	t_token	*match;

	match = AST_find_subparent(start);
	node = ft_malloc(sizeof(t_tree), 1);
	node->type = L_PARENTHESE;
	node->flag = start->flag;
	node->arg = NULL; // (
	node->left = AST(start->next, match);
	node->right = NULL;
	return (node);
}

void add_redir(t_tree *node, t_token *redirs_pos)
{
	t_redir *redirs_node;
	t_redir *tmp;	

	if (!redirs_pos->next){ // equivaut a ->    outfile > donc rien apres le redire 
		printf("bash: syntax error near unexpected token `newline'\n");
		exit(0);
	}
	redirs_node = ft_malloc(sizeof(t_redir), 1);
	redirs_node->value = redirs_pos->next->value;
	redirs_node->next = NULL;
	redirs_node->type = redirs_pos->type;
	tmp = node->redirs;
	if (!node->redirs)
		node->redirs = redirs_node;
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = redirs_node;
	}
}
