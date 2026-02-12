CFILES = ft_arg_len.c \
         ft_atoi.c \
         ft_lstadd_back.c \
         ft_lstclear.c \
         ft_lstnew.c \
         ft_lstsize.c \
         ft_split.c \
         ft_strdup.c \
         ft_strjoin.c \
         ft_strlen.c \
         ft_copy_cat.c \
         ft_sort_int_tab.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
#colors
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
RESET   := \033[0m

all: $(NAME)

$(NAME): $(OFILES) 
	@printf "$(GREEN)[Archivage] Archivage libft ...$(RESET)\n"
	ar rcs $@ $^

clean:
	@printf "$(YELLOW)[Nettoyage] Nettoyage fichiés objets ...$(RESET)\n"
	$(RM) $(OFILES)

fclean:
	@printf "$(YELLOW)[Nettoyage] Nettoyage global libft ...$(RESET)\n"
	$(RM) $(NAME) $(OFILES)

re: fclean all
