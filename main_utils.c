/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:52:12 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/07 15:53:42 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fail_line(t_env *env)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_free_all_malloc();
	free_env(&env);
	exit(0);
}

int	line_check1(char *line)
{
	if (line[0] == '\n' || line[0] == '\0' || only_spaces(line)
		|| only_tabs(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	line_check2(char *line)
{
	if (!check_parentheses(line) || !check_quotes(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

void	main_start_loop(t_env *env, char **line)
{
	if (g_signal != 0)
	{
		env->exit_status->exit_status = g_signal;
		g_signal = 0;
	}
	set_interactive_signals();
	(*line) = readline("minishell> ");
	if (!(*line))
		fail_line(env);
}

void	main_end_loop(char *line)
{
	ft_free_all_malloc();
	close_pipe();
	free(line);
}
