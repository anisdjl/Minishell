/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:19:00 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/01 18:59:21 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ast_check_start(t_token *token)
{
	if (token->type == AND || token->type == OR || token->type == PIPE)
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
				|| tmp->next->type == OR))
			state = 0;
		else if ((tmp->type == AND || tmp->type == OR)
			&& (tmp->next->type == R_PARENTHESE))
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
		if ((tmp->type == L_PARENTHESE && tmp->next->type == R_PARENTHESE))
			state = 0;
		else if ((tmp->type == WORD || tmp->type == F_FILE)
			&& tmp->next->type == L_PARENTHESE)
			state = 0;
		else if (tmp->type == R_PARENTHESE && (tmp->next->type == WORD
				|| tmp->next->type == F_FILE))
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
			&& (tmp->next->type == HERE_DOC || tmp->next->type == LEFT_A)
			|| (tmp->type == PIPE && (tmp->next->type == HERE_DOC
					|| tmp->next->type == APPEND || tmp->next->type == RIGHT_A
					|| tmp->next->type == LEFT_A)))
			state = 1;
		else if ((tmp->type != WORD && tmp->type != L_PARENTHESE
				&& tmp->type != R_PARENTHESE && tmp->type != F_FILE)
			&& ((tmp->next->type != WORD && tmp->next->type != L_PARENTHESE
					&& tmp->next->type != R_PARENTHESE
					&& tmp->next->type != F_FILE)))
			state = 0;
		tmp = tmp->next;
	}
	return (state);
}

int	ast_check(t_token *token)
{
	if (!ast_check_start(token))
		return (0);
	if (!check_around_subshell(&token))
		return (0);
	if (!check_cons_op_subshell(&token))
		return (0);
	if (!check_consecutive_op(&token))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}
