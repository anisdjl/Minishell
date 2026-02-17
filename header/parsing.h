/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:20:44 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/17 17:24:51 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

typedef struct s_tree
{
    char    **arg;
    int     type;
    struct s_tree *right;
    struct s_tree *left;
}   t_tree;

typedef struct	s_token
{
	char			*word; // le mot, la commande ou le separateur
	t_enum			type; // pour l'enum 
	int				flag; // avec le bit shifting
	struct s_token	*next; // le noeud d'apres (liste chainee)
}	t_token;

typedef struct	s_data
{
	t_token			*content; // un noeud de la liste chainee
	struct s_data	*data; // un autre neoud pour le parsing
}	t_data;

typedef enum s_enum
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
    
}   t_enum;

t_tree	*ft_lstnew(int content);
void	tokeniasation(char *line);

#endif