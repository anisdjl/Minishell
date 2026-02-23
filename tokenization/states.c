/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:43:05 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/23 11:10:59 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	general_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == ' ')
		create_token(lexer);
	else if (line[*y] == '\'')
	{
		lexer->state = SQUOTE;
		lexer->was_quoted = 1;
		lexer->current_flag |= F_SQUOTE;
	}
	else if (line[*y] == '\"')
	{
		lexer->state = DQUOTE;
		lexer->was_quoted = 1;
		lexer->current_flag |= F_DQUOTE;
	}
	else if (operator(line[*y]) && lexer->state == GENERAL)
		operator_token(lexer, line, y);
	else
		add_to_buffer(lexer, line[*y]);
}

void	squote_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == '\'')
		lexer->state = GENERAL;
	else
		add_to_buffer(lexer, line[*y]);
}

void	dquote_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == '\"')
		lexer->state = GENERAL;
	else
		add_to_buffer(lexer, line[*y]);
}
