/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/25 16:51:50 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	int fd;
	t_lexer	*lexer;

	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) == 4)
			return (0);
		history(line);
		if (!check_parentheses(line) || !check_quotes(line))
			continue;
		lexer = ft_lexer(line);
		if (!check_consecutive_op(&lexer->content))
		{
			printf("error\n");
			ft_free_all_malloc();
			free(line);
			continue;
		}
		debug_tokens(&lexer->content);
		ft_free_all_malloc();
		//free_struct(lexer);
		// ici mettre une free de tout (lexing, parsing, expand, exec)
		free(line);
	}
	return (0);
}
