/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:51:51 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/04 14:54:42 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

#include "../minishell.h"

int		exec_pipe_cmd(t_tree *node, t_env *env, int fd_in, int fd_out);
void	child_pipe(t_tree *node, t_env *env, int fd_in, int fd_out);
void	exec_pipe(char *path, char **paths, char **env_tab, char **arg);
void	add_pid_to_list(t_env *env, int pid);
int		wait_all_pids(t_env *env);
t_pid	*ft_lstnew_pid(int content);
void	ft_lstadd_back_pid(t_pid **lst, t_pid *new);
int		redir_for_pipes(t_tree *node, int *fd_in, int *fd_out);
int		redir_in_pipe(t_redir *redir, int *fd_in);
int		redir_out_pipe(t_redir *redir, int *fd_out);
void	handle_pipes(t_tree *node, t_env *env, int fd_in, int fd_out);

#endif