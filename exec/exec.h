/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:25:29 by anis              #+#    #+#             */
/*   Updated: 2026/03/04 10:52:56 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"

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

#endif