/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/04 14:33:11 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_lexer		*lexer;
	t_env		*env;
	t_tree		*ast;

	(void)argc;
	(void)argv;
	env = get_env(envp);
    while (1)
    {
		if (g_signal != 0)
		{
			env->exit_status->exit_status = g_signal;
			g_signal = 0;
		}
		set_interactive_signals();
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			ft_free_all_malloc();
			free_env(&env);
			exit(0);
		}
		if (line[0] == '\n' || line[0] == '\0' || only_spaces(line) || only_tabs(line)) // ajouter la secu pour le tab dans only spaces
		{   
			free(line); 
			continue;
		}
		set_execution_signals();
		history(line);
		if (!check_parentheses(line) || !check_quotes(line))
		{
			free(line);
			continue;
		}
		lexer = ft_lexer(line);
		ast = ast_launcher(lexer->content, env);
		pre_exec(ast, env);
		exec(ast, &env);
		ft_free_all_malloc();
		close_pipe();
		free(line);
	}
	return (0);
}
	