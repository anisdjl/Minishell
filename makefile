# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anis <anis@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 12:26:41 by adjelili          #+#    #+#              #
#    Updated: 2026/03/06 11:12:40 by anis             ###   ########.fr        #
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
	src/AST/AST_check.c \
	src/AST/AST.c \
	src/AST/AST_subshell.c \
	src/AST/AST_utils.c \
	env/env.c \
	exec/exec.c \
	exec/builtin.c \
	exec/exec_utils.c \
	exec/unset.c

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