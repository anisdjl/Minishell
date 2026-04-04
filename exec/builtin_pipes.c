/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:45:25 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/04 15:17:37 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	env_command_pipe(t_tree *node, t_env **env, int *fd_in, int *fd_out)
{
	t_env	*tmp;

	if (!env || !*env)
		exit (0);
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	tmp = *env;
	while(tmp)
	{
		if (tmp->key && ft_strlen(tmp->key) > 0 && tmp->value && ft_strlen(tmp->value) > 0)
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	(close((*fd_in)), close((*fd_out)));
	ft_free_all_malloc();
	free_env(env);
	exit (0);
}

int bultin_pipe_next(t_tree *node, t_env *env , int *fd_in, int *fd_out)
{
    char **arg;
    
    arg = args_to_tab(node->n_value);
    if (arg && arg[0] && ft_strlen(arg[0]) == 6
        && ft_strncmp(arg[0], "export", 6) == 0)
        return (export_pipe(node, &env, fd_in, fd_out));
    else if (arg && arg[0] && ft_strlen(arg[0]) == 5
        && ft_strncmp(arg[0], "unset", 5) == 0)
        return (unset_command_pipe(node, &env, fd_in, fd_out));
    else if (arg && arg[0] && ft_strlen(arg[0]) == 3
        && ft_strncmp(arg[0], "env", 3) == 0)
        return (env_command_pipe(node, &env, fd_in, fd_out));
    else if (arg && arg[0] && ft_strlen(arg[0]) == 4
        && ft_strncmp(arg[0], "exit", 4) == 0)
        exit_command_pipe(node, env, fd_in, fd_out);
    return (44444);
}

int    builtin_pipe(t_tree *node, t_env *env , int *fd_in, int *fd_out)
{
    char    **arg;

    wash_start(node->n_value);
    if (*fd_in != 0)
        dup2(*fd_in, 0);
    if (*fd_out != 1)
        dup2(*fd_out, 1);
    wash_start(node->n_value);
    arg = args_to_tab(node->n_value);
    if (arg && arg[0] && ft_strlen(arg[0]) == 4
        && ft_strncmp(arg[0], "echo", 4) == 0)
        return (echo_command_pipe(node, env, fd_in, fd_out));
    if (arg && arg[0] && ft_strlen(arg[0]) == 2 
        && ft_strncmp(arg[0], "cd", 2) == 0)
         return (cd_command_pipe(node, env, fd_in , fd_out));
    else if (arg && arg[0] && ft_strlen(arg[0]) == 3
        && ft_strncmp(arg[0], "pwd", 3) == 0)
        return (pwd_command_pipe(node, env, fd_in, fd_out));
    return (bultin_pipe_next(node, env, fd_in, fd_out));
}
