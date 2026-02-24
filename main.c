/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/24 15:43:14 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	int fd;
	t_lexer	*lexer;
	t_tree  *tree;

	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		if (!ft_strncmp(line, "exit", 4))
			return (0);
		history(line);	
		lexer = ft_lexer(line);
		tree = AST_launcher(lexer->content);
		free_struct(lexer);
		// ici mettre une free de tout (lexing, parsing, expand, exec)
		free(line);
	}
	return (0);
}
