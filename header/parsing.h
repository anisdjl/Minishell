/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:20:44 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/07 17:07:32 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define F_EXPAND (1 << 0)
# define F_DQUOTE (1 << 1)
# define F_SQUOTE (1 << 2)

typedef struct s_env	t_env;

typedef enum s_enum
{
	PIPE,
	OR,
	AND,
	WORD,
	HERE_DOC,
	RIGHT_A,
	LEFT_A,
	APPEND,
	SUBSHELL,
	L_PARENTHESE,
	R_PARENTHESE,
	F_FILE,
}						t_enum;

typedef enum s_state
{
	DQUOTE,
	SQUOTE,
	GENERAL,
	PARENTHESES,
}						t_state;

typedef struct s_token
{
	char				*value;
	t_enum				type;
	int					flag;
	struct s_token		*next;
}						t_token;

typedef struct s_value_node
{
	char				*value;
	int					type;
	int					flag;
	struct s_value_node	*next;
}						t_value_node;

typedef struct s_redir
{
	char				*value;
	int					type;
	int					flag;
	char				*file_name;
	struct s_redir		*next;
}						t_redir;

typedef struct s_tree
{
	t_value_node		*n_value;
	int					flag;
	int					fd_r;
	t_enum				type;
	t_redir				*redirs;
	t_token				*data;
	int					fd_in;
	int					fd_out;
	struct s_tree		*right;
	struct s_tree		*left;
}						t_tree;

typedef struct s_lexer
{
	t_token				*content;
	t_state				state;
	int					current_flag;
	char				buff[4096];
	int					index;
	int					was_quoted;
}						t_lexer;

void					add_to_buffer(t_lexer *lexer, char line);
void					create_token(t_lexer *lexer);
void					lexing(t_lexer *lexer, char *line);
t_lexer					*ft_lexer(char *line);
void					dquote_state(t_lexer *lexer, char *line, int *y);
void					squote_state(t_lexer *lexer, char *line, int *y);
void					general_state(t_lexer *lexer, char *line, int *y);
void					operator_token(t_lexer *lexer, char *line, int *y);
int						operator(char c);
t_enum					return_type(t_token *tmp);
void					put_types(t_lexer *lexer);
int						need_expand(t_token *tmp);
void					free_struct(t_lexer *lexer);
void					free_tokens(t_token **tokens);
int						check_quotes(char *line);
int						check_parentheses(char *line);
int						check_consecutive_op(t_token **token);
int						only_spaces(char *argv);
void					file_flag(t_token **tokens);
int						only_tabs(char *argv);

/*	AST	main func */

t_tree					*ast_launcher(t_token *token, t_env *env);
t_tree					*ast_op_node(t_token *op_pos);
t_tree					*ast(t_token *start, t_token *end);
t_token					*ast_eval_op(t_token *start, t_token *end);
t_tree					*ast_build_subshell(t_token *start, t_token *end);
void					add_redir(t_tree *node, t_token *redirs);
t_tree					*ast_value_node(t_token *start, t_token *end);

/* AST Check */

int						ast_check(t_token *token);
t_token					*ast_eval_op(t_token *start, t_token *end);

/* AST Utils */

t_token					*find_op(t_token *start, t_token *end, t_enum type);
int						count_word(t_token *start, t_token *end);
t_token					*ast_find_subparent(t_token *start);
int						check_consecutive_op(t_token **token);
void					add_subshell_redirs(t_tree *node, t_token *start,
							t_token *end);
int						is_subshell_redir(t_token *start, t_token *end);

/* AST lst Utils */

t_value_node			*ft_lstnew_value(char *content);
void					ft_lstadd_back_value(t_value_node **lst,
							t_value_node *new);

/* main */

void					fail_line(t_env *env);
int						line_check1(char *line);
int						line_check2(char *line);
void					main_start_loop(t_env *env, char **line);
void					main_end_loop(char *line);

#endif