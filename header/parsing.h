/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:20:44 by eprieur           #+#    #+#             */
/*   Updated: 2026/03/02 11:57:01 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# define F_EXPAND (1 << 0) // 001 un
# define F_DQUOTE (1 << 1) // 010 deux
# define F_SQUOTE (1 << 2) // 100 quatre

typedef struct s_env t_env;

typedef enum s_enum
{
	PIPE,     // | 0
	OR,       // || 1
	AND,      // && 2
	WORD,     // 3
	HERE_DOC, // << 4
	RIGHT_A,  // > 5
	LEFT_A,   // < 6
	APPEND,   // >> 7
	SUBSHELL, // 8
	L_PARENTHESE, // ( 9
	R_PARENTHESE, // ) 10
	F_FILE, // 11
}					t_enum;

typedef enum s_state
{
	DQUOTE,
	SQUOTE,
	GENERAL,
	PARENTHESES,
}					t_state;

typedef struct s_token
{
	char *value; // le mot, la commande ou le separateur
	t_enum type; // pour l'enum
	int				flag; // avec le bit shifting pour la priorite des operations
	struct s_token *next; // le noeud d'apres (liste chainee)
}					t_token;

typedef struct s_tree
{
	char			**arg;
	t_enum			type;
	int 			flag;
	t_token			*data;
	struct s_tree	*right;
	struct s_tree	*left;
}					t_tree;

typedef struct s_lexer
{
	t_token 		*content; // un noeud de la liste chainee
	t_state			state;
	int 			current_flag; // ne pas toucher ou utiliser
	char			buff[4096];
	int				index;
	int				was_quoted;
}					t_lexer;

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
int		only_spaces(char *argv);
void	file_flag(t_token **tokens);

/*	AST	main func */

t_tree				*AST_launcher(t_token *token, t_env *env);
t_tree				*AST_OP_NODE(t_token *op_pos);
t_tree				*AST(t_token *start, t_token *end);
t_token				*AST_EVAL_OP(t_token *start, t_token *end);
t_tree				*AST_build_subshell(t_token *start, t_token *end);
t_tree				*AST_VALUE_NODE(t_token *start, t_token *end);

/* AST Check */

int 				AST_check(t_token *token);

/* AST Utils */

t_token				*find_op(t_token *start, t_token *end, t_enum type);
void 				print_ast(t_tree *tree, char *prefix, int is_left);
int					AST_check_start(t_token *token);
int					count_word(t_token *start, t_token *end);
t_token				*AST_find_subparent(t_token *start, t_token *end);
t_tree				*subshell_start(t_token *start, t_token *end);
int					claim_subshell(t_token *start, t_token *end); // pour plus tard

#endif