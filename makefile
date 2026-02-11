# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 12:26:41 by adjelili          #+#    #+#              #
#    Updated: 2026/02/11 16:51:36 by eprieur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = main.c \
	src/history/history.c

OBJ = $(SRC:.c=.o)

NAME = minishell

READLINE_DIR = $(shell brew --prefix readline)

INCLUDES = -I$(READLINE_DIR)/include
LFLAGS = -L$(READLINE_DIR)/lib -lreadline

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJ)
	
fclean : clean
	rm -f $(NAME)
	
re : fclean all

.PHONY: all clean fclean re