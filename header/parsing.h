/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:20:44 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/20 16:54:34 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum	s_enum
{
	PIPE,
	OR,
	AND,
	WORD,
    //SINGLE_QUOTES, on ne stocke pas les quotes
    //DOUBLE_QUOTES, on ne stocke pas les doubles quotes
	EXPAND, // est ce que je ne metterais pas juste un flag ?
	HERE_DOC,
	RIGHT_A, // >
	LEFT_A, // <
	D_LEFT_A, // <<
	D_RIGHT_A, // >>
	SUB_STR, // () subshell
} t_enum;

typedef enum s_state
{
	DQUOTE,
	SQUOTE,
	GENERAL,
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
	t_token			**content; // un noeud de la liste chainee
	t_state			state;
	char			buff[4096];
	int				index;
}	t_lexer;

void	debug_tokens(t_token **tokens);
void	add_to_buffer(t_lexer *lexer, char line); // le remplissage de buffer
void	create_token(t_lexer *lexer, t_enum type);
void	lexing(t_lexer *lexer, char *line);
t_lexer	*ft_lexer(char *line);
void	dquote_state(t_lexer *lexer, char *line, int *y);
void	squote_state(t_lexer *lexer, char *line, int *y);
void	general_state(t_lexer *lexer, char *line, int *y);
void	operator_token(t_lexer *lexer, char *line, int *y);
int	operator(char c);

#endif