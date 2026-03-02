#include "../../minishell.h"

t_token	*AST_find_subparent(t_token *start, t_token *end)
{
	t_token *op;
	int		count;

	op = NULL;
	count = 0;
	while (start && start != end)
	{
		if (start->type == L_PARENTHESE)
			count++;
		if (start->type == R_PARENTHESE)
			count--;
		if (count == 0)
			return (start);
		start = start->next;
	}
	return (op);
}

t_tree	*AST_build_subshell(t_token *start, t_token *end)
{
	t_tree	*node;
	t_token	*match;

	match = AST_find_subparent(start, end);
	node = ft_malloc(sizeof(t_tree), 1);
	node->type = L_PARENTHESE;
	node->flag = start->flag;
	node->arg = NULL;
	node->left = AST(start->next, match);
	node->right = NULL;
	return (node);
}
