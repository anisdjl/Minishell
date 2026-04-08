# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 12:26:41 by adjelili          #+#    #+#              #
#    Updated: 2026/04/07 16:48:33 by eprieur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g -Wall -Werror -Wextra

SRC = main.c \
      main_utils.c \
      src/history/history.c \
      src/signals/signals.c \
      src/garbage_collector/gc1.c \
      src/garbage_collector/gc2.c \
      src/env/env.c \
      src/env/env2.c \
      tokenization/tokenization.c \
      tokenization/flags_and_types.c \
      tokenization/states.c \
      tokenization/free_tokens.c \
      tokenization/check.c \
      src/ast/synthax_check.c \
      src/ast/ast.c \
      src/ast/ast_subshell.c \
      src/ast/ast_utils.c \
      src/ast/ast_utils2.c \
      src/expand/extraction.c \
      src/expand/expand.c \
      src/expand/wash_quote.c \
      src/expand/expand_case.c \
      src/expand/expand_split.c \
      src/exec/exec.c \
      src/exec/cd.c \
      src/exec/cd_pipe.c \
      src/exec/exit.c \
      src/exec/exit_utils.c \
      src/exec/exec_utils2.c \
      src/exec/redir.c \
      src/exec/redir2.c \
      src/exec/builtin.c \
      src/exec/exec_utils.c \
      src/exec/unset.c \
      src/exec/export.c \
      src/exec/pipes.c \
      src/exec/pipes2.c \
      src/exec/pipes3.c \
      src/exec/pipes4.c \
      src/exec/butltin_utils.c \
      src/exec/builtin_pipes.c \
      src/exec/builtin_pipes2.c \
      src/exec/exit_pipes.c \
      src/exec/here_doc.c \
      src/exec/echo_pipes.c \
      src/exec/pwd_pipe.c \
      src/exec/here_doc_utils.c \
      src/exec/exec_subshell.c \
      src/exec/exec_child.c \
      src/exec/exec_empty.c
	
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
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_PATH)
	
fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)
re : fclean all

.PHONY: all clean fclean re