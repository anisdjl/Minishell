/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:32:59 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/07 16:11:18 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	write_in_file_lp1(char *line, t_redir *redir, t_env *env)
{
	int	exit;

	if (line == NULL)
	{
		if (g_signal == 130)
		{
			close(env->fd_w);
			env->exit_status->exit_status = 130;
			exit = 1;
			return (exit);
		}
		ft_putstr_fd("minishell: here-document at line 1", 2);
		ft_putstr_fd(" delimited by end-of-file", 2);
		ft_putstr_fd("(wanted ('", 2);
		ft_putstr_fd(redir->value, 2);
		ft_putstr_fd("')\n", 2);
		close(env->fd_w);
		env->exit_status->exit_status = 0;
		exit = 0;
		return (exit);
	}
	return (-1);
}

int	write_in_file_check(char *line, t_redir *redir, t_env *env)
{
	if (ft_strlen(line) == ft_strlen(redir->value) && ft_strncmp(redir->value,
			line, ft_strlen(redir->value)) == 0)
	{
		close(env->fd_w);
		free(line);
		return (1);
	}
	write(env->fd_w, line, ft_strlen(line));
	write(env->fd_w, "\n", 1);
	free(line);
	return (0);
}

int	write_in_file(t_tree *node, t_env *env, t_redir *redir)
{
	char				*line;
	int					saved_in;
	struct sigaction	sa;
	int					exit;

	(void)node;
	exit = 0;
	saved_in = dup(STDIN_FILENO);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handler_heredoc;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		line = readline("> ");
		exit = write_in_file_lp1(line, redir, env);
		if (exit >= 0 || write_in_file_check(line, redir, env))
			break ;
	}
	dup2(saved_in, STDIN_FILENO);
	close(saved_in);
	set_interactive_signals();
	return (exit);
}
