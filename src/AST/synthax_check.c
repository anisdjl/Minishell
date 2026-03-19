#include "../../minishell.h"

int	AST_check_start(t_token *token)
{
	if (token->type == AND || token->type == OR)
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			token->value);
		return (0);
	}
	while (token->next)
		token = token->next;
	if (token->type != WORD && token->type != R_PARENTHESE
		&& token->type != F_FILE)
	{
		if (token->type == HERE_DOC || token->type == APPEND)
			printf("minishell: syntax error near unexpected token 'newline'\n");
		else
			printf("minishell: syntax error near unexpected token '%s'\n",
				token->value);
		return (0);
	}
	return (1);
}

int	check_cons_op_subshell(t_token **token)
{
	t_token	*tmp;
	int		state;

	tmp = (*token);
	state = 1;
	while (tmp->next)
	{
		if (tmp->type == L_PARENTHESE && (tmp->next->type == AND
				|| tmp->next->type == OR)) //  ( && echo hello)
			state = 0;
		else if (tmp->type == L_PARENTHESE && (tmp->next->type == AND
				|| tmp->next->type == OR))
			state = 0;
		tmp = tmp->next;
	}
	if (state == 0)
		printf("minishell: syntax error near unexpected token '%s'\n",
			tmp->value);
	return (state);
}

int	check_around_subshell(t_token **token)
{
	t_token	*tmp;
	int		state;

	tmp = (*token);
	state = 1;
	while (tmp->next)
	{
		if ((tmp->type == L_PARENTHESE && tmp->next->type == R_PARENTHESE)) //()
			state = 0;
		else if ((tmp->type == WORD || tmp->type == F_FILE)
			&& tmp->next->type == L_PARENTHESE) // echo hello (echo hello)
			state = 0;
		else if (tmp->type == R_PARENTHESE && (tmp->next->type == WORD
				|| tmp->next->type == F_FILE)) // (echo hello) echo hello
			state = 0;
		tmp = tmp->next;
	}
	if (state == 0)
		printf("minishell: syntax error near unexpected token '%s'\n",
			tmp->value);
	return (state);
}

int	check_consecutive_op(t_token **token)
{
	t_token	*tmp;
	int		state;

	tmp = (*token);
	state = 1;
	while (tmp->next)
	{
		if ((tmp->type == AND || tmp->type == OR)
			&& (tmp->next->type == HERE_DOC || tmp->next->type == LEFT_A)) // || <<, || <, && <<,&& < 
			state = 1;
		else if ((tmp->type != WORD && tmp->type != L_PARENTHESE
				&& tmp->type != R_PARENTHESE && tmp->type != F_FILE)
			&& ((tmp->next->type != WORD && tmp->next->type != L_PARENTHESE
					&& tmp->next->type != R_PARENTHESE
					&& tmp->next->type != F_FILE)))
			state = 0;
		tmp = tmp->next;
	}
	if (state == 0)
		printf("minishell: syntax error near unexpected token '%s'\n",
			tmp->value);
	return (state);
}

int	AST_check(t_token *token)
{
	if (!AST_check_start(token))
		return (0);
	if (!check_around_subshell(&token))
		return (0);
	if (!check_cons_op_subshell(&token))
		return (0);
	if (!check_consecutive_op(&token))
		return (0);
	return (1);
}

// if (flag & F_EXPAND)
// (echo a &&)
// (echo a ||)

/*
	En plusieur fonction :

	- is_valid_operator_sequence()
	- is_valid_redirection()
	- is_balanced_quotes()
	- is_valid_pipe_chain()

*/