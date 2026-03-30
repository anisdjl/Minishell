/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/30 16:41:01 by adjelili         ###   ########.fr       */
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
	t_tree		*ast;

	//sig();
	env = get_env(envp);
   // domain_expand(tmp_tree(), env); // Sert au test de l'expand
    while (1)
    {
		if (g_signal != 0)
			env->exit_status->exit_status += g_signal;
		set_interactive_signals();
		line = readline("minishell> ");
		if (!line)
		{
			break;
			// // write(1, "\n", 1);
			// ft_free_all_malloc();
			// free_env(&env);
			// exit(0);
		}
		if (line[0] == '\n' || line[0] == '\0' || only_spaces(line) || only_tabs(line)) // ajouter la secu pour le tab dans only spaces
		{   
			free(line); 
			continue;
		}
		set_execution_signals();
		history(line);
		if (!check_parentheses(line) || !check_quotes(line))
			continue;
		lexer = ft_lexer(line);
		ast = AST_launcher(lexer->content);
		pre_exec(ast, env);
		exec(ast, &env);
		// printf("%d\n", env->exit_status->exit_status);
		ft_free_all_malloc();
		//free env
		free(line);
	}
	return (0);
}
	