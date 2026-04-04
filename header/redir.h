/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:06:52 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/04 15:08:48 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "../minishell.h"

int		redir_function(t_tree *node);
int		redir_in(t_redir *redir);
int		redir_out(t_redir *redir);
void	save_fds(int *fd_in, int *fd_out);
void	reset_and_close(int *fd_in, int *fd_out);
int		env_command_for_export(t_tree *node, t_env **env);
int		check_existant(t_env *env, char *key);
char	*strip_quotes_redir(const char *src);
int		redir_is_directory(char *path);

#endif