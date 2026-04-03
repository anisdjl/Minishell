# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 12:26:41 by adjelili          #+#    #+#              #
#    Updated: 2026/04/03 19:07:05 by eprieur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g -Wall -Werror -Wextra

SRC = main.c \
	src/history/history.c \
	tokenization/tokenization.c \
	tokenization/flags_and_types.c \
	tokenization/states.c \
	tokenization/free_tokens.c \
	garbage_collector/gc1.c \
	garbage_collector/gc2.c \
	tokenization/check.c \
	src/ast/synthax_check.c \
	src/ast/ast.c \
	src/ast/ast_subshell.c \
	src/ast/ast_utils.c \
	src/ast/ast_utils2.c \
	src/expand/extraction.c \
	env/env.c \
	exec/exec.c \
	exec/cd.c \
	exec/cd_pipe.c \
	exec/exit.c \
	exec/exec_utils2.c \
	exec/redir.c \
	exec/redir2.c \
	exec/builtin.c \
	exec/exec_utils.c \
	exec/unset.c \
	exec/export.c \
	exec/pipes.c \
	exec/butltin_utils.c \
	exec/builtin_pipes.c \
	exec/builtin_pipes2.c \
	exec/exit_pipes.c \
	exec/here_doc.c \
	src/expand/expand.c \
	src/expand/wash_quote.c \
	src/expand/expand_case.c \
	src/expand/expand_split.c \
	signals/signals.c

OBJ = $(SRC:.c=.o)

NAME = minishell

LIBFT_PATH = libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

INCLUDES = -I$(READLINE_DIR)/include
LFLAGS = -L$(READLINE_DIR)/lib -lreadline

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(LFLAGS) -o $(NAME)

$(LIBFT_LIB) :
	$(MAKE) -C $(LIBFT_PATH)

%.o : %.c
	$(CC) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_PATH)
	
fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)
re : fclean all

.PHONY: all clean fclean re