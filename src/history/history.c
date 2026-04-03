/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 19:19:07 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/03 19:19:09 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void  history(char *line)
{
	// int fd;

	// if (access(".minishell_history", F_OK) == -1)
	// {
	// 	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0700);
	// 	if (fd == -1)
    //         return ;
	// }
	// else
	// 	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND);
	add_history(line);
	// write(fd, line, ft_strlen(line));
	// write(fd, "\n", 1);
}
