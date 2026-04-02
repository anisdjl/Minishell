/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:28:25 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/02 11:39:16 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	save_fds(int *fd_in, int *fd_out)
{
	*fd_in = dup(0);
	*fd_out = dup(1);
}

void	reset_and_close(int *fd_in, int *fd_out)
{
	dup2(*fd_in, 0);
	dup2(*fd_out, 1);
	close(*fd_in);
	close(*fd_out);
}

int	redir_function(t_tree *node)
{
	t_redir	*tmp;
    t_redir	*next;
	int		return_value;

	if (!node->redirs)
		return (0);
	tmp = node->redirs;
	return_value = 0;
	while (tmp)
	{
		if (tmp->type == 6)
			return_value = (redir_in(tmp));
		else if (tmp->type == 5 || tmp->type == 7)
			return_value = (redir_out(tmp));
		else if (tmp->type == HERE_DOC)
        {
            next = tmp->next;
            while (next && next->type != HERE_DOC)
                next = next->next;
            if (!next)
                return_value = heredoc_redir(node);
        }
		if (return_value != 0)
			return (return_value);
		tmp = tmp->next;
	}
	return (return_value);
}

int	redir_is_directory(char *path)
{
    struct stat	st;

    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(path, 2);
        ft_putendl_fd(": Is a directory", 2);
		ft_free_all_malloc();
        return (1);
    }
    return (0);
}

int	redir_in(t_redir *redir)
{
    int		fd_in;
    char	*path;

    path = strip_quotes_redir(redir->value);
    if (!path)
        return (1);
    if (redir_is_directory(path))
        return (1);
    if (access(path, F_OK | R_OK) == -1)
    {
    	ft_putstr_fd("minishell: ", 2); // pas sur si il faut le laisser
        perror(path);
		ft_free_all_malloc();
        return (1);
    }
    fd_in = open(path, O_RDONLY);
    if (fd_in < 0)
		return (error_message(path));
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        close(fd_in);
		ft_free_all_malloc();
        return (1);
    }
    close(fd_in);
    return (0);
}
