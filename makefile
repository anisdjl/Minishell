# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 12:26:41 by adjelili          #+#    #+#              #
#    Updated: 2026/02/11 15:47:35 by adjelili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = main.c

OBJ = $(SRC:.c=.o)

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o -lreadline $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
	
fclean : clean
	rm -f $(NAME)
	
re : fclean all

.PHONY: all clean fclean re