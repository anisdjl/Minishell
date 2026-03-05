#include "../../minishell.h"

t_tree	*AST_VALUE_NODE(t_token *start, t_token *end)
{
	t_tree	*node;
	int		i;

	i = 0;
	node = ft_malloc(sizeof(t_tree), 1);
	node->arg = ft_malloc(sizeof(char *), count_word(start, end) + 1);
	if (!node->arg)
		return (NULL);
	node->type = WORD;
	while (start && start != end)
	{
		if (start->type == WORD)
			node->arg[i++] = start->value;
		else if (start->type >= 4 && start->type <= 7)
		{
			add_redir(node, start);
			if (start->next) // > outfile
				start = start->next;
		}
		start = start->next;
	}
	node->arg[i] = NULL;
	return (node);
}

t_tree	*AST_OP_NODE(t_token *op_pos)
{
	t_tree	*node;

	node = ft_malloc(sizeof(t_tree), 1);
	node->arg = ft_malloc(sizeof(char *), 2);
	node->type = op_pos->type;
	node->data = op_pos;
	node->arg[0] = op_pos->value;
	node->arg[1] = NULL;
	return (node);
}

t_tree	*AST(t_token *start, t_token *end)
{
	t_tree	*node;
	t_token	*op_pos;
	t_token *match;

	node = NULL;
	op_pos = NULL;
	if (start == NULL || start == end)
		return (NULL);
	if (start->type == L_PARENTHESE)
	{
		match = AST_find_subparent(start); //check pos de )
		if (match->next == end) //si au debut ou si le subshell est mise a part
			return (AST_build_subshell(start, AST_find_subparent(start)));
	}
	op_pos = AST_EVAL_OP(start, end);
	if (!op_pos)
		return (AST_VALUE_NODE(start, end));
	node = AST_OP_NODE(op_pos);
	node->left = AST(start, op_pos);
	node->right = AST(op_pos->next, end);
	return (node);
}

t_tree	*AST_launcher(t_token *token)
{
	t_tree *ast; // construit directement l'AST à partir du premier token

	if (!token)	
		return (NULL);
	if (!AST_check(token)){
		return (NULL);
	}
	ast = AST(token, NULL);
	printf("\n--- AST Structure ---\n");
    print_ast(ast, "", 0);
    printf("---------------------\n\n");
	return (ast);
}
