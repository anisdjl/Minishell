/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:07:42 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/03 18:17:36 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec(t_tree *ast, t_env *env)
{
	int	status;
	
	status = 0;
	// if (ast->type == AND)
	// {
	// 	status = exec(ast->left, env);
	// 	if (status == 0)
	// 		return (exec(ast->right, env));
	// 	return (status);
	// }
	// else if (ast->type == OR)
	// {
	// 	status = exec(ast->left, env);
	// 	if (status != 0)
	// 		return (exec(ast->right, env));
	// 	return (status);
	// }
	// else if (ast->type == PIPE)
	// 	return (handle_pipes(ast, env));
	// else if (ast->type == WORD)
	return (exec_cmd(ast, env));
	return (1);
}

// int	handle_pipes(t_tree *node, t_env *env)
// {
// 	int	pipe_fd[2];
// 	int	pid;

// 	if (pipe(pipe_fd) == -1);
// 	{
// 		ft_free_all_malloc();
// 		exit(EXIT_FAILURE); // ou relancer minishell ?
// 	}
// 	pid = fork();
// 	(close(pipe_fd[0]), close(pipe_fd[1]));
// 	if (pid < 0)
// 	{
// 		ft_free_all_malloc();
// 		exit(EXIT_FAILURE); // ou relancer minishell
// 	}
// 	if (pid == 0)
// 	{
// 		if (node->type == )
// 		dup2(pipe_fd[1], )
// 		exec(node->left, env);
// 	}
// 	// wait_for_childrens
// }

int	exec_cmd(t_tree *node, t_env *env)
{
	// if (ft_strlen(node->arg[0]) == 4
	// 	&& ft_strncmp(node->arg[0], "echo", 4) == 0)
	// 	echo_command(node, env);
	if (ft_strlen(node->arg[0]) == 2 
		&& ft_strncmp(node->arg[0], "cd", 2) == 0)
	 	return (cd_command(node, env));
	else if (ft_strlen(node->arg[0]) == 3
		&& ft_strncmp(node->arg[0], "pwd", 3) == 0)
		return (pwd_command(node, env));
	// else if (ft_strlen(node->arg[0]) == 6
	// 	&& ft_strcmp(node->arg[0], "export", 6) == 0)
	// 	export_command(node, env);
	// else if (ft_strlen(node->arg[0]) == 5
	// 	&& ft_strncmp(node->arg[0], "unset", 5) == 0)
	// 	unset_command(node, env);
	else if (ft_strlen(node->arg[0]) == 3
		&& ft_strncmp(node->arg[0], "env", 3) == 0)
		env_command(node, env);
	// else if (ft_strlen(node->arg[0]) == 4
	// 	&& ft_strncmp(node->arg[0], "exit", 4) == 0)
	// 	exit_command(node, env);
	else
		return (exec_normal_command(node, env));
	return (1);
}

int	exec_normal_command(t_tree *node, t_env *env)
{
	int	pid;
	char	*path;
	int		status = 0;
	char	**paths;
	

	if ((pid = fork()) < 0)
	{
		ft_free_all_malloc();
		exit(EXIT_FAILURE); // ou affiche juste le prompt
	}
	if (pid == 0) // on est dans le fils
	{
		paths = get_paths(env_to_tab(&env));
		if (only_spaces(node->arg[0]) || node->arg[0][0] == '\0')
		{
			printf("command not found\n");
			return(0);
		}
		if (!given_path(node->arg[0]))
			path = find_path(node->arg[0], paths);
		else
			path = ft_strdup(node->arg[0]);
		execve(path, node->arg, env_to_tab(&env));
		printf("error  while executing the command\n");
	}
	waitpid(pid, NULL, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
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

char	*find_path(char *cmd, char **env)
{
	int		y;
	char	*path_v1;
	char	*path_joined;

	path_v1 = ft_strjoin("/", cmd);
	y = 0;
	while (env[y])
	{
		path_joined = ft_strjoin(env[y], path_v1);
		if (access(path_joined, F_OK | X_OK) == 0)
			return (free (path_v1), path_joined);
		else
		{
			y++;
			free(path_joined);
		}
	}
	free (path_v1);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	// ft_free_pipes(pipes, data);
	// ft_free_data(data);
	// ft_free_paths(cmd);
	exit(127);
}

char **env_to_tab(t_env **env)
{
	t_env	*tmp;
	char	**env_tab;
	int		y;

	if (!env || !*env)
		return (NULL);
	y = 0;
	tmp = (*env);
	env_tab = ft_malloc(1, sizeof(char *) * ft_lstsize_env(*env) + 1);
	while (tmp)
	{
		env_tab[y] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
		y++;
	}
	return (env_tab);
}

int	ft_lstsize_env(t_env *lst)
{
	int	y;

	y = 0;
	while (lst)
	{
		lst = lst->next;
		y++;
	}
	return (y);
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
