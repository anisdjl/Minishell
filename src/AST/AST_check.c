#include "../../minishell.h"

int	AST_check_start(t_token *token)
{
	if (token->type != L_PARENTHESE && token->type != RIGHT_A
		&& token->type != HERE_DOC && token->type != LEFT_A
		&& token->type != APPEND && token->type != WORD)
        {
            printf("bash: syntax error near unexpected token '%s'\n", token->value);
		    return (0);
        }
	while (token->next)
		token = token->next;
	if (token->type != WORD && token->type != R_PARENTHESE)
    {
        if (token->type == HERE_DOC || token->type == APPEND)
            printf("bash: syntax error near unexpected token 'newline'\n");
        else 
            printf("bash: syntax error near unexpected token '%s'\n", token->value);
        return (0);
    }
	return (1);
}

int AST_check(t_token *token)
{
    if (!AST_check_start(token))
        return (0);
    if (!check_consecutive_op(&token))
        return (0);
    return (1);
}
