/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:31:02 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/14 15:30:09 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_path(char *cmd, char **env)
{
	int		y;
	char	*path_v1;
	char	*path_joined;

	path_v1 = ft_strjoin("/", cmd);
	y = 0;
	if (!env || !*env)
		exit(127);
	while (env[y])
	{
		path_joined = ft_strjoin(env[y], path_v1);
		if (access(path_joined, F_OK | X_OK) == 0)
			return (path_joined);
		else
			y++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	// ft_free_pipes(pipes, data);
	// ft_free_data(data);
	// ft_free_paths(cmd);
	exit(127);
}

char	**get_paths(char **envp)
{
	int		y;
	char	**paths;
	char	*path;

	y = 0;
	while (envp[y])
	{
		if (ft_strncmp(envp[y], "PATH=", 5) == 0)
		{
			path = ft_strchr(envp[y], '/');
			paths = ft_split(path, ':');
			return (paths);
		}
		else
			y++;
	}
	return (NULL);
}

int	given_path(char *cmd)
{
	int	a;

	a = 0;
	while (cmd[a])
	{
		if (cmd[a] == '/')
			return (1);
		else
			a++;
	}
	return (0);
}

int	valid_export(char *args)
{
	int	y;

	y = 0;
	if (args[0] == '\0' || only_spaces(args) || (!((args[0] >= 'a' && args[0] <= 'z') 
        || (args[0] >= 'A' && args[0] <= 'Z') 
        || (args[0] == '_'))))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);	
		return (1);
	}
	while (args[++y] && args[y] != '=')
	{
		if (!ft_isalnum(args[y]) && args[y] != '_')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);	
			return (1);
		}
	}
	return (0);
}
