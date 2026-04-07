/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 15:51:57 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_lexer	*lexer;
	t_env	*env;
	t_tree	*ast;

	(void)argc;
	(void)argv;
	line = NULL;
	env = get_env(envp);
	while (1)
	{
		main_start_loop(env, &line);
		if (line_check1(line))
			continue ;
		set_execution_signals();
		history(line);
		if (line_check2(line))
			continue ;
		lexer = ft_lexer(line);
		ast = ast_launcher(lexer->content, env);
		if (!pre_exec(ast, env))
			exec(ast, &env);
		main_end_loop(line);
	}
	return (0);
}
