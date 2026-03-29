/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:29:52 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/29 15:22:11 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_pipes(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	fd[2];
	int	pid;

	if (node->type == PIPE)
	{
		if (pipe(fd) < 0)
		{
			ft_free_all_malloc();
			exit(EXIT_FAILURE); // + free env
		}
		handle_pipes(node->left, env, fd_in , fd[1]);
		close(fd[1]);
		handle_pipes(node->right, env, fd[0], fd_out);
		close(fd[0]);
	}
	else if (node->type == WORD)
	{
		pid = exec_pipe_cmd(node, env, fd_in, fd_out);
		add_pid_to_list(env, pid);
	}
}

int	exec_pipe_cmd(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_free_all_malloc();
		exit(EXIT_FAILURE); // + free env
	}
	if (pid == 0)
	{
		if (redir_for_pipes(node, &fd_in, &fd_out))
			exit (1);
		if (builtin_pipe(node, env, &fd_in, &fd_out) == 44444)
		{
			child_pipe(node, env, fd_in, fd_out);
		}
	}
	return (pid);
}

void	child_pipe(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	char	*path;
	char	**paths;
	char	**env_tab;
	char	**arg;

	wash_start(node->n_value);
	arg = args_to_tab(node->n_value);
	env_tab = env_to_tab(&env);
	paths = get_paths(env_tab);
	if (arg && arg[0] && (only_spaces(arg[0]) || arg[0][0] == '\0'))
	{
		ft_putstr_fd("minsihell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (126);
	}
	if (arg && arg[0] && !given_path(arg[0]))
		path = find_path(arg[0], paths);
	else
		path = ft_strdup(arg[0]);
	if (fd_in != 0)
		(dup2(fd_in, 0), close(fd_in));
	if (fd_out != 1)
		(dup2(fd_out, 1), close(fd_out));
	exec_pipe(path, paths, env_tab, arg);
}

void	exec_pipe(char *path, char **paths, char **env_tab, char **arg)
{
	execve(path, arg, env_tab);
	if (errno == EACCES)
	{
    	ft_putstr_fd("minishell: ", 2);
    	ft_putstr_fd(arg[0], 2);
   		ft_putstr_fd(": Permission denied\n", 2);
    	exit(126);
	}
	if (errno == EISDIR)
	{
    	ft_putstr_fd("minishell: ", 2);
    	ft_putstr_fd(arg[0], 2);
    	ft_putstr_fd(": Is a directory\n", 2);
    	exit(126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_free_all_malloc();
	exit (127);
}

void	add_pid_to_list(t_env *env, int pid)
{
	t_pid	*pid_new;

	pid_new = ft_lstnew_pid(pid);
	ft_lstadd_back_pid(&env->pid, pid_new);
}

int	wait_all_pids(t_env *env)
{
	t_pid	*tmp;
	int		status;

	tmp = env->pid;
	while (tmp->next)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	waitpid(tmp->pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status->exit_status = WEXITSTATUS(status);
	return (env->exit_status->exit_status);
}

t_pid	*ft_lstnew_pid(int content)
{
	t_pid	*new_node;

	new_node = malloc(sizeof(t_pid));
	if (!new_node)
		return (NULL);
	new_node->pid = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_pid(t_pid **lst, t_pid *new)
{
	t_pid	*ptr;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		ptr = *lst;
		while (ptr->next)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}

int	redir_for_pipes(t_tree *node, int *fd_in, int *fd_out)
{
	t_redir	*tmp;
	int		return_value;

	return_value = 0;
	if (!node->redirs)
		return (0);
	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->type == 6)
			return_value = (redir_in_pipe(tmp, fd_in));
		else if (tmp->type == 5 || tmp->type == 7)
			return_value = (redir_out_pipe(tmp, fd_out));
		if (return_value != 0)
			return (return_value);
		tmp = tmp->next;
	}
	return (return_value);
}

int	redir_in_pipe(t_redir *redir, int *fd_in)
{
    int		fd;
    char	*path;

    path = strip_quotes_redir(redir->value);
    if (!path)
        return (1);
    if (redir_is_directory(path))
        return (free(path), 1);
    if (access(path, F_OK | R_OK) == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(path);
        return (free(path), 1);
    }
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(path);
        return (free(path), 1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        return (free(path), 1);
    }
    close(fd);
    *fd_in = 0;
    free(path);
    return (0);
}

int	redir_out_pipe(t_redir *redir, int *fd_out)
{
    int		fd;
    char	*path;

    path = strip_quotes_redir(redir->value);
    if (!path)
        return (1);
    if (redir_is_directory(path))
        return (free(path), 1);
    if (redir->type == 5)
        fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else
        fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(path);
        return (free(path), 1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        return (free(path), 1);
    }
    close(fd);
    *fd_out = 1;
    free(path);
    return (0);
}
