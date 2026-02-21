/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/21 15:06:49 by adjelili         ###   ########.fr       */
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
	put_types(lexer);
	debug_tokens(&lexer->content);
	return (lexer);
}

int	operator(char c)
{
	if (c == '>' || c == '<'
		|| c == '|'
		|| c == '&')
		return (1);
	else
		return (0);
}
void	operator_token(t_lexer *lexer, char *line, int *y)
{
	if (operator(line[*y]) && line[*y + 1] != line[*y])
	{
		create_token(lexer);
		add_to_buffer(lexer, line[*y]);
		create_token(lexer);
	}
	else if (operator(line[*y]) && line[*y + 1] == line[*y])
	{
		create_token(lexer);
		add_to_buffer(lexer, line[*y]);
		add_to_buffer(lexer, line[*y + 1]);
		create_token(lexer);
		(*y)++;
	}
	else
		return ;
}

void	general_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == ' ')
		create_token(lexer);
	else if (line[*y] == '\'')
	{
		lexer->state = SQUOTE;
		lexer->current_flag |= F_SQUOTE;
	}
	else if (line[*y] == '\"')
	{
		lexer->state = DQUOTE;
		lexer->current_flag |= F_DQUOTE;
	}
	else if (line[*y] == '(')
	{
		add_to_buffer(lexer, line[*y]);
		lexer->state = PARENTHESES;
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

void	par_state(t_lexer *lexer, char *line, int *y)
{
	if (line[*y] == ')')
		lexer->state = GENERAL;
	add_to_buffer(lexer, line[*y]);
}

void	lexing(t_lexer *lexer, char *line)
{
	int	y;

	lexer->current_flag = 0;
	y = 0;
	while (line[y])
	{
		if (lexer->state == GENERAL)
			general_state(lexer, line, &y);
		else if (lexer->state == SQUOTE)
			squote_state(lexer, line, &y);
		else if (lexer->state == DQUOTE)
			dquote_state(lexer, line, &y);
		else if (lexer->state == PARENTHESES)
			par_state(lexer, line, &y);
		y++;
	}
	create_token(lexer); // pour le dernier element de la commande si il n'y a pas d'espaces
}

void	create_token(t_lexer *lexer)
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
		new->type = 0;
		new->flag = lexer->current_flag;
		lexer->index = 0;
		ft_lstadd_back(&lexer->content, new);
		if (lexer->current_flag != 0)
			lexer->current_flag = 0;
	}
}

void	put_types(t_lexer *lexer)
{
	t_token	*tmp;

	tmp = lexer->content;
	while (tmp)
	{
		tmp->type = return_type(tmp);
		tmp = tmp->next;
	}
	tmp = lexer->content;
	while (tmp)
	{
		if (need_expand(tmp))
			tmp->flag |= F_EXPAND;
		tmp = tmp->next;
	}
}

int	need_expand(t_token *tmp)
{
	int y;

	if (tmp->flag & F_SQUOTE)
		return (0);
	y = 0;
	while (tmp->value[y])
	{
		if (tmp->value[y] == '$' && tmp->value[y + 1] && tmp->value[y + 1] != ' ')
			return (1);
		else if (tmp->value[y] == '*' && !(tmp->flag & F_DQUOTE))
			return (1);
		y++;
	}
	return (0);
}

t_enum	return_type(t_token *tmp)
{
	if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '|')
		return (PIPE);
	else if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, "||", 2) == 0)
		return (OR);
	else if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, "&&", 2) == 0)
		return (AND);
	if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, "<<", 2) == 0)
		return (HERE_DOC);
	if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, ">>", 2) == 0)
		return (APPEND);
	if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '>')
		return (RIGHT_A);
	if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '>')
		return (LEFT_A);
	else
		return (WORD);
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

/*
ls "" avec rien entre les dquote_state
ls '' avec rien entre les squote_state
echo "hello le vrai bash attend une suite mais on devrait juste afficher une erreur
ls > sans fichier ca doit afficher erreur avant meme d'executer
| ls ou ls | erreur de stntaxe directement (une seule commande dans un pipe)
echo $non_existent doit afficher rien avec un retour a la ligne
pareil pour echo "$non existent"
echo $ ou echo "$" doit afficher $ et pas d'expand
comme dans pipex si on donne un chemin absolu il ne cherche pas dans l'env
*/