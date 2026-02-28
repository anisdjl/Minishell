/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:25:29 by anis              #+#    #+#             */
/*   Updated: 2026/02/28 22:29:02 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"
#include "../env/env.h"

int		ft_lstsize_env(t_env *lst);
int		exec(t_tree *ast, t_env *env);
int		handle_pipes(t_tree *node, t_env *env);
int		exec_cmd(t_tree *node, t_env *env);
char 	**env_to_tab(t_env **env);

#endif