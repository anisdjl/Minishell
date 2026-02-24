#include "../../minishell.h"

t_tree	*AST_build_subshell(t_token *start, t_token *end)
{
	t_tree	*node;
	t_token	*op_pos;

	if (start == NULL)
		return (NULL);
	node = NULL;
	op_pos = NULL;
	op_pos = AST_EVAL(start, end);

    printf("[AST] Build start ... \n");
	if (!op_pos && start->type == WORD)
		return (AST_VALUE_NODE(start, end));
	if (!op_pos){
		printf("[AST] Undefined\n"); // temporaire
		return (NULL);
	}
	node = AST_OP_NODE(op_pos);
	node->left = AST_build_subshell(start, op_pos);
	node->right = AST_build_subshell(op_pos->next, end);
	return (node);
}