/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volt <volt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/11 16:37:00 by volt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	int fd;
	
	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		history(line);
	}
	return (0);
}
