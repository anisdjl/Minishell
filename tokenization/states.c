/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:43:05 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/30 16:43:51 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	general_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == ' ' || line[*y] == '\t')
		create_token(lexer);
	else if (line[*y] == '\'')
	{
		lexer->state = SQUOTE;
		lexer->was_quoted = 1;
		lexer->current_flag |= F_SQUOTE;
		add_to_buffer(lexer, line[*y]);
	}
	else if (line[*y] == '\"')
	{
		lexer->state = DQUOTE;
		lexer->was_quoted = 1;
		lexer->current_flag |= F_DQUOTE;
		add_to_buffer(lexer, line[*y]);
	}
	else if ((operator(line[*y]) || (line[*y] == '(' || line[*y] == ')'))
		&& lexer->state == GENERAL)
		operator_token(lexer, line, y);
	else
		add_to_buffer(lexer, line[*y]);
}

void	squote_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == '\'')
		lexer->state = GENERAL;
	add_to_buffer(lexer, line[*y]);
}

void	dquote_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == '\"')
		lexer->state = GENERAL;
	add_to_buffer(lexer, line[*y]);
}
