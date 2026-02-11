/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/11 16:09:42 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	
	int fd;
	
	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	line = readline("minishell> ");
	printf("%s\n", line);
	if (line)
	{
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
	}
	return (0);
}
