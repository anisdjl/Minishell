/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:20:44 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/16 15:28:24 by eprieur          ###   ########.fr       */
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

typedef struct s_lexer
{
	int 			type;
	int 			priority;
	char			*value;
	struct s_lexer	*next;
}	t_lexer;

typedef enum s_token
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
    
}   t_token;

t_tree	*ft_lstnew(int content);
void	tokeniasation(char *line);

#endif