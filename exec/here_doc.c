/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:03:24 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/04 16:31:14 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*generate_herdoc_name(int index)
{
	char	*name;
	char	*number;

	number = ft_itoa(index);
	name = ft_strjoin(".heredoc_tmp_", number);
	return (name);
}

int	here_doc(t_tree *node, t_env *env)
{
	t_redir	*tmp;
	int		return_value;

	return_value = 0;
	if (!node->redirs)
		return (0);
	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			return_value = create_file(node, env, tmp);
			return_value = write_in_file(node, env, tmp);
		}
		tmp = tmp->next;
	}
	env->exit_status->exit_status = return_value;
	return (return_value);
}

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

int	create_file(t_tree *node, t_env *env, t_redir *redir)
{
	static int	i = 0;

	redir->file_name = generate_herdoc_name(i);
	i++;
	env->fd_w = open(redir->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (env->fd_w < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(""); // mettre le bon message d'erreur
		return (1);
	}
	if (node->fd_r > 2)
		close(node->fd_r);
	node->fd_r = open(redir->file_name, O_RDONLY); // pas besoin
	if (node->fd_r < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("");
		return (1);
	}
	unlink(redir->file_name);
	return (0);
}

int	heredoc_redir(t_tree *node)
{
	int	value;

	value = dup2(node->fd_r, 0);
	if (value < 0)
	{
		perror("Error: ");
		return (value);
	}
	close(node->fd_r);
	return (0);
}

int	pre_exec(t_tree *node, t_env *env)
{
	int	return_value;

	return_value = 0;
	if (!node)
		return (0);
	if (node && (node->type == AND || node->type == OR || node->type == PIPE))
	{
		if (node->left)
			return (pre_exec(node->left, env));
		if (node->right)
			return (pre_exec(node->right, env));
	}
	else if (node && node->left && node->type == SUBSHELL)
		return (pre_exec(node->left, env));
	else if (node && node->type == WORD)
		return (here_doc(node, env));
	return (return_value);
}
