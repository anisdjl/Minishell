#include "../../minishell.h"

t_token	*AST_EVAL_OP(t_token *start, t_token *end)
{
	t_token	*op_pos;

	op_pos = find_op(start, end, OR);
	if (!op_pos)
		op_pos = find_op(start, end, AND);
	if (!op_pos)
		op_pos = find_op(start, end, PIPE);
	if (!op_pos)
		op_pos = find_op(start, end, RIGHT_A);
	if (!op_pos)
		op_pos = find_op(start, end, LEFT_A);
	if (!op_pos)
		op_pos = find_op(start, end, HERE_DOC);
	if (!op_pos)
		op_pos = find_op(start, end, APPEND);
	return (op_pos);
}

t_tree	*AST_VALUE_NODE(t_token *start, t_token *end)
{
	t_tree	*node;
	int		i;

	i = 0;
	node = ft_malloc(sizeof(t_tree), 1);
	node->arg = ft_malloc(sizeof(char *), count_word(start, end) + 1);
	if (!node->arg)
		return (NULL);
	while (start != end && start->type == WORD)
	{
		node->arg[i] = start->value;
		start = start->next;
		i++;
	}
	node->arg[i] = NULL;
	node->left = NULL;
	node->right = NULL;
	node->type = WORD;
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

	node = NULL;
	op_pos = NULL;
	if (start == NULL)
		return (NULL);
	op_pos = AST_EVAL_OP(start, end);
	if (!op_pos && start->type == WORD)
		return (AST_VALUE_NODE(start, end));
	if (!op_pos && start->type == L_PARENTHESE)
	{
		printf("[AST] Subshell find ...\n");
		return (AST_build_subshell(start, end));
	}
	if (!op_pos && (start->type == RIGHT_A || start->type == LEFT_A))
	{
		printf("[AST] Redir find ...");
		return (NULL);
	}
	node = AST_OP_NODE(op_pos);
	node->left = AST(start, op_pos);
	node->right = AST(op_pos->next, end);
	return (node);
}

t_tree	*AST_launcher(t_token *token, t_env *env)
{
	t_tree *ast; // construit directement l'AST à partir du premier token
	if (!token)
		return (NULL);
	if (!AST_check(token))
		return (NULL);
	ast = AST(token, NULL);
	printf("\n--- AST Structure ---\n");
	print_ast(ast, "", 0);
	printf("---------------------\n\n");
	return (ast);
}
