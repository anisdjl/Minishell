/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/23 12:55:56 by adjelili         ###   ########.fr       */
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
	ft_bzero(lexer->buff, 4094);
	lexer->content = NULL;
	lexing(lexer, line);
	put_types(lexer);
	debug_tokens(&lexer->content);
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

	if (lexer->index == 0)
		return ;
	else if (ft_strlen(lexer->buff) > 0 || lexer->was_quoted == 1)
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
		ft_bzero(lexer->buff, 4095);
		if (lexer->current_flag != 0)
			lexer->current_flag = 0;
		if (lexer->was_quoted)
			lexer->was_quoted = 0;
	}
	else
		return ;
}

void	add_to_buffer(t_lexer *lexer, char line) // le remplissage de buffer
{
	if (lexer->index < 4095)
		lexer->buff[lexer->index] = line;
	lexer->index++;
}

void    debug_tokens(t_token **tokens)
{
    t_token *tmp;
    int     i;

    if (!tokens || !*tokens)
    {
        printf("\033[1;31m[Lexer] La liste est vide ou inexistante.\033[0m\n");
        return ;
    }
    tmp = *tokens;
    i = 0;
    printf("\n\033[1;34m--- DEBUG TOKENS ---\033[0m\n");
    while (tmp)
    {
        printf("\033[1;32mToken [%d]\033[0m\n", i);
        
        // Si la value est NULL (sécurité) ou si le premier caractère est \0 (token vide)
        if (!tmp->value)
            printf("  Value : \033[1;31m(NULL)\033[0m\n");
        else if (tmp->value[0] == '\0')
            printf("  Value : \033[1;35mEMPTY_TOKEN (quotes)\033[0m\n");
        else
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