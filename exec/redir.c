/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:28:25 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/29 14:55:29 by adjelili         ###   ########.fr       */
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
			return_value = heredoc_redir(node);
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
        return (1);
    }
    return (0);
}

// int	redir_in(t_redir *redir)
// {
// 	int	fd_in;

// 	if (access(redir->value, R_OK | F_OK) == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		perror(redir->value);
// 		return (1);
// 	}
// 	fd_in = open(redir->value, O_RDONLY);
// 	if (fd_in < 0)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		perror(redir->value);
// 		return (1);
// 	}
// 	dup2(fd_in, 0);
// 	close(fd_in);
// 	return (0);
// }

// int redir_in(t_redir *redir)
// {
//     int         fd_in;
//     struct stat path_stat;

//     // 1. On récupère les infos du fichier
//     if (stat(redir->value, &path_stat) == 0)
//     {
//         // 2. Si c'est un dossier, c'est une erreur de redirection
//         if (S_ISDIR(path_stat.st_mode))
//         {
//             ft_putstr_fd("minishell: ", 2);
//             ft_putstr_fd(redir->value, 2);
//             ft_putendl_fd(": Is a directory", 2);
//             return (1);
//         }
//     }
//     // 3. On check les accès classiques
//     if (access(redir->value, R_OK | F_OK) == -1)
//     {
//         ft_putstr_fd("minishell: ", 2);
//         perror(redir->value);
//         return (1);
//     }
//     // 4. Ouverture et dup2
//     fd_in = open(redir->value, O_RDONLY);
//     if (fd_in < 0)
//     {
//         ft_putstr_fd("minishell: ", 2);
//         perror(redir->value);
//         return (1);
//     }
//     if (dup2(fd_in, STDIN_FILENO) == -1)
//     {
//         close(fd_in);
//         return (1);
//     }
//     close(fd_in);
//     return (0);
// }

int	redir_in(t_redir *redir)
{
    int		fd_in;
    char	*path;

    path = strip_quotes_redir(redir->value);
    if (!path)
        return (1);
    if (redir_is_directory(path))
        return (free(path), 1);
    if (access(path, F_OK | R_OK) == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(path);
        return (free(path), 1);
    }
    fd_in = open(path, O_RDONLY);
    if (fd_in < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(path);
        return (free(path), 1);
    }
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        close(fd_in);
        return (free(path), 1);
    }
    close(fd_in);
    free(path);
    return (0);
}

// int	redir_out(t_redir *redir)
// {
// 	int	fd_out;

// 	if (redir->type == 5)
// 		fd_out = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else if (redir->type == 7)
// 		fd_out = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (fd_out < 0)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		perror(redir->value);
// 		return (1);	
// 	}
// 	if (access(redir->value, W_OK) == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		perror(redir->value);
// 		return (1);
// 	}
// 	dup2(fd_out, 1);
// 	close(fd_out);
// 	return (0);
// }

int	redir_out(t_redir *redir)
{
    int		fd_out;
    char	*path;

    path = strip_quotes_redir(redir->value);
    if (!path)
        return (1);
    if (redir_is_directory(path))
        return (free(path), 1);
    if (redir->type == 5)
        fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else
        fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd_out < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(path);
        return (free(path), 1);
    }
    if (dup2(fd_out, STDOUT_FILENO) == -1)
    {
        close(fd_out);
        return (free(path), 1);
    }
    close(fd_out);
    free(path);
    return (0);
}

char	*strip_quotes_redir(const char *src)
{
    char	*dst;
    int		i;
    int		j;

    if (!src)
        return (NULL);
    dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
    if (!dst)
        return (NULL);
    i = 0;
    j = 0;
    while (src[i])
    {
        if (src[i] != '\'' && src[i] != '\"')
            dst[j++] = src[i];
        i++;
    }
    dst[j] = '\0';
    return (dst);
}
