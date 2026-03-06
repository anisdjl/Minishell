/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:25:29 by anis              #+#    #+#             */
/*   Updated: 2026/03/06 18:43:50 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"


typedef struct	s_pid
{
	int				pid;
	struct s_pid	*next;
}	t_pid;

int		ft_lstsize_env(t_env *lst);
int		exec(t_tree *ast, t_env *env);
int		handle_pipes(t_tree *node, t_env *env);
int		exec_cmd(t_tree *node, t_env *env);
char 	**env_to_tab(t_env **env);
char	*find_path(char *cmd, char **env);
int		given_path(char *cmd);
int		exec_normal_command(t_tree *node, t_env *env);
char	**get_paths(char **envp);
int		cd_command(t_tree *node, t_env *env);
int 	pwd_command(t_tree *node, t_env *env);
int		size_of_table(char **tab);
int		env_command(t_tree *node, t_env **env);
int		echo_command(t_tree *node, t_env *env);
int		check_n(char *args);
int		echo_command2(t_tree *node, t_env *env);
int		valid_unset(char **args);
int		unset_command(t_tree *node, t_env **env);
int		redir_function(t_tree *node);
int		redir_in(t_redir *redir);
int		redir_out(t_redir *redir);
void	save_fds(int *fd_in, int *fd_out);
void	unset_node(t_env **env, char *arg);
void	reset_and_close(int *fd_in, int *fd_out);
// int		ft_lstsize_arg(t_node_value *node_value);
int		child(t_tree *node, t_env *env);
int		env_command_for_export(t_tree *node, t_env **env);
int		export(t_tree *node, t_env *env);
int		env_command_for_export(t_tree *node, t_env **env);

#endif