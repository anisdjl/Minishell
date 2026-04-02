/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:03:24 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/02 15:25:05 by adjelili         ###   ########.fr       */
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

void	here_doc(t_tree *node, t_env *env)
{
	t_redir	*tmp;
	int		return_value;

	return_value = 0;
	if (!node->redirs)
		return ;
	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			return_value = create_file(node, env, tmp);
			write_in_file(node, env, tmp);
		}
		tmp = tmp->next;
	}
	env->exit_status->exit_status = return_value;
}

void	write_in_file(t_tree *node, t_env *env, t_redir *redir)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_putstr_fd("minishell: here-document at line 1 delimited by end-of-file", 2);
			close(env->fd_w);
			env->exit_status->exit_status = 0;
			free(line);
			break ;
		}
		if (ft_strlen(line) == ft_strlen(redir->value)
		&& (ft_strncmp(redir->value, line, ft_strlen(redir->value)) == 0))
		{
			close(env->fd_w);
			free(line);
			break ;
		}
		write(env->fd_w, line, ft_strlen(line));
		write(env->fd_w, "\n", 1);
		free(line);
	}
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
	node->fd_r = open(redir->file_name, O_RDONLY); //pas besoin
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
	int value;

	value =	dup2(node->fd_r, 0);
	if (value < 0)
	{
		perror("Error: ");
		return (value);
	}
	close(node->fd_r);
	return (0);
	// if (access(node->redirs->file_name, R_OK | F_OK) == -1)
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	perror("je suis ici"); // mettre le bon message d'erreur
	// 	return (1);
	// }
	// fd_in = open(node->redirs->file_name, O_RDONLY);
	// if (fd_in < 0)
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	perror("ou ici"); // mettre le bon message d'erreur
	// 	return (1);
	// }
	// dup2(fd_in, 0);
	// close(fd_in);
	// unlink(node->redirs->file_name);
	// return (0);
}

void	pre_exec(t_tree *node, t_env *env)
{
	if (!node)
		return ;
	if (node && (node->type == AND || node->type == OR || node->type == PIPE))
	{
		if (node->left)
			pre_exec(node->left, env);
		if (node->right)
			pre_exec(node->right, env);
	}
	else if (node && node->left && node->type == SUBSHELL)
		pre_exec(node->left, env);
	else if (node && node->type == WORD)
		here_doc(node, env);
}

// int main(void)
// {
// 	static int i = 0;

// 	while (i < 5)
// 	{
// 		printf("%s\n", generate_herdoc_name(i));
// 		i++;
// 	}
// 	return (0);
// }