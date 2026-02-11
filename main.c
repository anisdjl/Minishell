/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/11 15:45:09 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	
	//line = malloc(sizeof(char) * 1000);
	
	line = readline("minishell> ");
	// char buffer[1096];
	// printf("%s\n", getenv("PATH"));
	// printf("%s\n", getcwd(buffer, 1096));
	// chdir("/home");
	
	// printf("%s", getcwd(buffer, 1096));
	return (0);
}
