/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 10:15:34 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/02 11:36:10 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redir_out(t_redir *redir)
{
    int		fd_out;
    char	*path;

    path = strip_quotes_redir(redir->value);
    if (!path)
        return (1);
    if (redir_is_directory(path))
        return (1);
    if (redir->type == 5)
        fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else
        fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd_out < 0)
		return (error_message(path));
    if (dup2(fd_out, STDOUT_FILENO) == -1)
    {
        close(fd_out);
		ft_free_all_malloc();
        return (1);
    }
    close(fd_out);
    return (0);
}

char	*strip_quotes_redir(const char *src)
{
    char	*dst;
    int		i;
    int		j;

    if (!src)
        return (NULL);
    dst = ft_malloc(1, sizeof(char) * (ft_strlen(src) + 1));
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

int	error_message(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	perror(path);
    return (1);
}
