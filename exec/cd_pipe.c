/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:26:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/03 16:15:25 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cd_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	char	current_dir[4096];
	char	**arg;

	arg = args_to_tab(node->n_value);
	if (redir_function(node))
		exit (1);
	getcwd(current_dir, 4096);
	if (!arg[1])
		exit (go_to_home(node, env, fd_in, fd_out, current_dir));
	if (size_of_table(arg) > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit (1);
	}
	if (ft_strlen(arg[1]) == 1 && arg[1][0] == '-')
		exit (return_to_old_pwd(node, env, current_dir, fd_in, fd_out));
	if (chdir(arg[1]) != 0)
	{
		ft_putstr_fd(arg[0], 2);
		write(2, ": ", 2);
		perror(arg[1]);
		(close((*fd_in)), close((*fd_out)));
		exit (1);
	}
	extract_oldpwd(node->n_value, env, current_dir);
	(close((*fd_in)), close((*fd_out)));
	exit (0);
}	
