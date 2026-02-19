/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/19 10:07:23 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		exit(EXIT_FAILURE); // + free tout le reste
	lexer->state = GENERAL;
	lexer->index = 0;
	lexing(lexer);
	return (lexer);
}

void	lexing(t_lexer *lexer, char *line)
{
	int	y;

	y = 0;
	while (line[y])
	{
		if (lexer->state == GENERAL)
		{
			if (line[y] == ' ')
				create_token(lexer);
			else if (line[y] == '\'')
				lexer->state = SQUOTE;
			else if (line[y] == '\"')
				lexer->state = DQUOTE;
			else
				add_to_buffer(lexer, line[y])
		}
		else if (lexer->state == SQUOTE)
		{
			if (line[y] == '\'')
				lexer->state = GENERAL
			add_to_buffer(lexer, line[y]);
		}
		else if (lexer->state == DQUOTE)
		{
			if (line[y] == '\"')
				lexer->state = GENERAL;
			else
				add_to_buffer(lexer, line[y])
		}
		y++;
	}
}

void	create_token(t_lexer *lexer, t_enum type)
{
	if (lexer->index == 0)
		return ;
	else
	{
		lexer;>content = malloc(sizeof(t_token));
		if (!lexer->content)
			exit(EXIT_FAILURE); // + free tout le reste
		lexer->content->value = malloc(sizeof(char) * ft_strlen(lexer->buff));
		if (!lexer->content->value)
			exit(EXIT_FAILURE); // + tout les free
		lexer->content->word = ft_strdup(buff);
		lexer->content->next = NULL;
		lexer->content->type = type;
		lexer->index = 0;
	}
}
void	add_to_buffer(t_lexer *lexer, char line)
{
	if (line == ' ')
		create_token(lexer, 0);
	lexer->buff[lexer->index] = line;
	lexer->index++;
}

// void	general_state(t_lexer *lexer, char *line)
// {
	
// }

// void	squote_state(t_lexer *lexer, char *line)
// {
	
// }

// void	dquote_state(t_lexer *lexer, char *line)
// {

// }
