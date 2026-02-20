/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/20 17:19:22 by anis             ###   ########.fr       */
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
	lexer->content = malloc(sizeof(t_token));
	if (!lexer->content)
		exit(EXIT_FAILURE); // + free tout le reste
	lexer->content = NULL;
	lexing(lexer, line);
	debug_tokens(&lexer->content);
	return (lexer);
}

int	operator(char c)
{
	if (c == '>' || c == '<'
		|| c == '|' || c == '$'
		|| c == '&' || c == '*')
		return (1);
	else
		return (0);
}
void	operator_token(t_lexer *lexer, char *line, int *y)
{
	if (operator(line[*y]) && !operator(line[*y + 1]))
	{
		create_token(lexer, 0);
		add_to_buffer(lexer, line[*y]);
		create_token(lexer, 0);
	}
	else if (operator(line[*y]) && line[*y + 1] == line[*y])
	{
		create_token(lexer, 0);
		add_to_buffer(lexer, line[*y]);
		add_to_buffer(lexer, line[*y + 1]);
		create_token(lexer, 0);
		(*y)++;
	}
	else
		return ;
}

void	general_state(t_lexer *lexer, char *line, int *y)
{
	t_enum type = 0;
	if (line[*y] == ' ')
		create_token(lexer, type);
	else if (line[*y] == '\'')
		lexer->state = SQUOTE;
	else if (line[*y] == '\"')
		lexer->state = DQUOTE;
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

void	lexing(t_lexer *lexer, char *line)
{
	int	y;
	t_enum type = 0;
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
	create_token(lexer, type); // pour le dernier element de la commande si il n'y a pas d'espaces
}

void	create_token(t_lexer *lexer, t_enum type) // creation de token
{
	t_token	*new;

	if (lexer->index == 0)
		return ;
	else
	{
		lexer->buff[lexer->index] = '\0';
		new = malloc(sizeof(t_token));
		if (!new)
			exit(EXIT_FAILURE); // + tout les frees
		new->value = ft_strdup(lexer->buff);
		new->next = NULL;
		new->type = type;
		lexer->index = 0;
		ft_lstadd_back(&lexer->content, new);
	}
}
void	add_to_buffer(t_lexer *lexer, char line) // le remplissage de buffer
{
	if (lexer->index < 4095)
		lexer->buff[lexer->index] = line;
	lexer->index++;
}

void	debug_tokens(t_token **tokens)
{
	t_token	*tmp;
	int		i;

	if (!tokens || !*tokens)
	{
		printf("\033[1;31m[Lexer] La liste est vide.\033[0m\n");
		return ;
	}
	tmp = *tokens;
	i = 0;
	printf("\n\033[1;34m--- DEBUG TOKENS ---\033[0m\n");
	while (tmp)
	{
		printf("\033[1;32mToken [%d]\033[0m\n", i);
		printf("  Value : \033[1;33m[%s]\033[0m\n", tmp->value);
		printf("  Type  : %u\n", tmp->type);
		printf("  Flag  : %d\n", tmp->flag);
		printf("--------------------\n");
		tmp = tmp->next;
		i++;
	}
	printf("\033[1;34m--- END DEBUG ---\033[0m\n\n");
}
