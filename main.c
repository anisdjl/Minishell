/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/21 14:28:55 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	int fd;

	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		history(line);
		ft_lexer(line);
		// ici mettre une free de tout (lexing, parsing, expand, exec)
		free(line);
	}
	return (0);
}
