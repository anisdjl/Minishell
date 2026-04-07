/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:23:23 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/07 16:10:33 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void	child(t_tree *node, t_env *env)
{
	char	*path;
	char	**paths;
	char	**env_tab;
	char	**arg;

	arg = args_to_tab(node->n_value);
	env_tab = env_to_tab(&env);
	paths = get_paths(env_tab);
	if (arg && arg[0] && (only_spaces(arg[0]) || arg[0][0] == '\0'))
	{
		ft_putstr_fd("minsihell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(126);
	}
	if (arg && arg[0] && !given_path(arg[0]))
		path = find_path(arg[0], paths, &env);
	else
		path = ft_strdup(arg[0]);
	execve(path, arg, env_tab);
	error_execve(arg, env);
}
