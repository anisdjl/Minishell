/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/08 11:58:52 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = ft_malloc(1, sizeof(t_lexer));
	if (!lexer)
		exit(EXIT_FAILURE);
	lexer->state = GENERAL;
	lexer->index = 0;
	ft_bzero(lexer->buff, 4094);
	lexer->content = NULL;
	lexing(lexer, line);
	put_types(lexer);
	return (lexer);
}

void	lexing(t_lexer *lexer, char *line)
{
	int	y;

	lexer->current_flag = 0;
	lexer->was_quoted = 0;
	y = 0;
	while (line[y])
	{
		if (lexer->state == GENERAL)
			general_state(lexer, line, &y);
		else if (lexer->state == SQUOTE)
			squote_state(lexer, line, &y);
		else if (lexer->state == DQUOTE)
			dquote_state(lexer, line, &y);
		y++;
	}
	create_token(lexer);
}

void	create_token(t_lexer *lexer)
{
	t_token	*new;

	if (lexer->index == 0 && lexer->was_quoted == 0)
		return ;
	else if (ft_strlen(lexer->buff) > 0 || lexer->was_quoted == 1)
	{
		lexer->buff[lexer->index] = '\0';
		new = ft_malloc(1, sizeof(t_token));
		if (!new)
			exit(EXIT_FAILURE);
		if (lexer->index == 0)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(lexer->buff);
		new->next = NULL;
		new->type = 0;
		new->flag = lexer->current_flag;
		lexer->index = 0;
		ft_lstadd_back(&lexer->content, new);
		ft_bzero(lexer->buff, 4095);
		lexer->current_flag = 0;
		lexer->was_quoted = 0;
	}
}

void	add_to_buffer(t_lexer *lexer, char line)
{
	if (lexer->index < 4095)
		lexer->buff[lexer->index] = line;
	lexer->index++;
}
