# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 12:26:41 by adjelili          #+#    #+#              #
#    Updated: 2026/02/18 10:51:52 by adjelili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = main.c \
	src/history/history.c \
	tokenization/tokenization.c 

OBJ = $(SRC:.c=.o)

NAME = minishell

READLINE_DIR = $(shell brew --prefix readline)

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
	
fclean : clean
	rm -f $(NAME)
	
re : fclean all

.PHONY: all clean fclean re