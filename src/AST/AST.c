#include "../../minishell.h"

t_token	*AST_EVAL(t_token *start, t_token *end)
{
	t_token	*op_pos;

	op_pos = find_op(start, end, OR);
	if (!op_pos)
		op_pos = find_op(start, end, AND);
	if (!op_pos)
		op_pos = find_op(start, end, PIPE);
	if (!op_pos && start->type == L_PARENTHESE)
		op_pos = start;
	return (op_pos);
}

t_tree	*AST_VALUE_NODE(t_token *start, t_token *end)
{
	t_tree	*node;
	int		i;

	i = 0;
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->arg = malloc((count_word(start, end) + 1) * sizeof(char *));
	if (!node->arg)
		return (NULL);
	while (start != end && start->type == WORD)
	{
		node->arg[i] = start->value;
		start = start->next;
		i++;
	}
	node->arg[i] = NULL;
	node->type = WORD;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree	*AST_OP_NODE(t_token *op_pos)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->arg = malloc(2 * sizeof(char *));
	if (!node->arg)
		return (NULL);
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

	if (start == NULL)
		return (NULL);
	node = NULL;
	op_pos = NULL;
	op_pos = AST_EVAL(start, end);
	
	if (!op_pos && start->type == WORD)
		return (AST_VALUE_NODE(start, end));
	if (!op_pos){
		printf("[AST] Undefined\n"); // temporaire
		return (NULL);
	}
	if (op_pos && op_pos->type == L_PARENTHESE){
		printf("Subshell find ! \n");
		//fonction creation node
		return (NULL); // temporaire
	}
	node = AST_OP_NODE(op_pos);
	node->left = AST(start, op_pos);
	node->right = AST(op_pos->next, end);
	return (node);
}

t_tree	*AST_launcher(t_token *token)
{
	if (!token)
		return (NULL);
	t_tree *ast; // construit directement l'AST à partir du premier token
	ast = AST(token, NULL);
	print_ast(ast, 0);
	return (ast);
}
