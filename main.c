/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/14 16:07:44 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int main(int argc, char **argv, char **envp)
{
    char *line;
    int fd;
    t_lexer		*lexer;
	t_env		*env;

	sig();
	env = get_env(envp);
    while (1)
    {
		if (g_signal != 0)
			env->exit_status->exit_status += g_signal;
		//sig(env);
		line = readline("minishell> ");
		if (!line)
		{
			// write(1, "\n", 1);
			ft_free_all_malloc();
			// free_env;
			exit(0);
		}
		if (line[0] == '\n' || line[0] == '\0' || only_spaces(line))
		{   
			free(line); 
			continue;
		}
		history(line);
		if (!check_parentheses(line) || !check_quotes(line))
			continue;
		lexer = ft_lexer(line);
		exec(AST_launcher(lexer->content), env);
		printf("%d\n", env->exit_status->exit_status);
		ft_free_all_malloc();
		//free env
		free(line);
	}
	return (0);
}
