/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:20:44 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/25 15:39:22 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# define F_EXPAND (1 << 0) // 001 un
# define F_DQUOTE (1 << 1) // 010 deux
# define F_SQUOTE (1 << 2) // 100 quatre

typedef enum	s_enum
{
	PIPE, // | 0
	OR, // || 1
	AND, // && 2
	WORD, // 3
	HERE_DOC, // << 4
	RIGHT_A, // > 5
	LEFT_A, // < 6
	APPEND, // >> 7
	L_PARENTHESE, // (
	R_PARENTHESE, // )
} t_enum;

typedef enum s_state
{
	DQUOTE,
	SQUOTE,
	GENERAL,
	PARENTHESES,
}	t_state;

typedef struct s_tree
{
    char    **arg;
    int     type;
    struct s_tree *right;
    struct s_tree *left;
}   t_tree;

typedef struct	s_token
{
	char			*value; // le mot, la commande ou le separateur
	t_enum			type; // pour l'enum 
	int				flag; // avec le bit shifting pour la priorite des operations
	struct s_token	*next; // le noeud d'apres (liste chainee)
}	t_token;

typedef struct	s_lexer
{
	t_token	*content; // un noeud de la liste chainee
	t_state	state;
	int		current_flag; // ne pas toucher ou utiliser
	char	buff[4096];
	int		index;
	int		was_quoted;
}	t_lexer;

void	debug_tokens(t_token **tokens);
void	add_to_buffer(t_lexer *lexer, char line); // le remplissage de buffer
void	create_token(t_lexer *lexer);
void	lexing(t_lexer *lexer, char *line);
t_lexer	*ft_lexer(char *line);
void	dquote_state(t_lexer *lexer, char *line, int *y);
void	squote_state(t_lexer *lexer, char *line, int *y);
void	general_state(t_lexer *lexer, char *line, int *y);
void	operator_token(t_lexer *lexer, char *line, int *y);
int		operator(char c);
t_enum	return_type(t_token *tmp);
void	put_types(t_lexer *lexer);
int		need_expand(t_token *tmp);
void	free_struct(t_lexer *lexer);
void	free_tokens(t_token **tokens);
int		check_quotes(char *line);
int		check_parentheses(char *line);
int		check_consecutive_op(t_token **token);

#endif