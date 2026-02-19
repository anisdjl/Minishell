/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:20:44 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/19 10:08:30 by adjelili         ###   ########.fr       */
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
    SINGLE_QUOTES,
    DOUBLE_QUOTES,
    EXPAND,
    HERE_DOC,
    RIGHT_A, // >
    LEFT_A, // <
    D_LEFT_A, // <<
    D_RIGHT_A, // >>
    SUB_STR, // ()
    
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
	t_token			*content; // un noeud de la liste chainee
	t_state			state;
	char			buff[4096];
	int				index;
}	t_lexer;

#endif