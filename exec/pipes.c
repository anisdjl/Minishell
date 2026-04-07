/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:29:52 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 14:42:41 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	close_extra_fds(t_tree *node, int fd_in, int fd_out);

static int	exec_pipe_subshell(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		ft_free_all_malloc();
		free_env(&env);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close_extra_fds(node, fd_in, fd_out);
		if (redir_for_pipes(node, &fd_in, &fd_out) != 0)
		{
			free_env(&env);
			ft_free_all_malloc();
			exit(1);
		}
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		status = exec(node->left, &env);
		free_env(&env);
		ft_free_all_malloc();
		close_pipe();
		exit (status);
	}
	return (pid);
}

static void	close_extra_fds(t_tree *node, int fd_in, int fd_out)
{
    int	fd;
	int	heredoc_fd;
	t_redir	*redir;

	heredoc_fd = -1;
	redir = node->redirs;
	while (redir)
	{
		if (redir->type == HERE_DOC && node->fd_r > 2)
			heredoc_fd = node->fd_r;
		redir = redir->next;
	}

    fd = 3;
    while (fd < 1024)
    {
		if (fd != fd_in && fd != fd_out && fd != heredoc_fd)
            close(fd);
        fd++;
    }
}

void	close_pipe(void)
{
	int fd;

	fd = 3;
	while (fd < 1024)
	{
		if (fd != STDERR_FILENO && fd != STDIN_FILENO && fd != STDOUT_FILENO)
			close (fd);
		fd++;
	}
}

void	handle_pipes(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	fd[2];
	int	pid;

	if (node->type == PIPE)
	{
		if (pipe(fd) < 0)
		{
			ft_free_all_malloc();
			free_env(&env);
			exit(EXIT_FAILURE);
		}
		handle_pipes(node->left, env, fd_in , fd[1]);
		close(fd[1]);
		if (fd_in != 0)
            close(fd_in);
		handle_pipes(node->right, env, fd[0], fd_out);
		close(fd[0]);
	}
	else if (node->type == WORD)
	{
		pid = exec_pipe_cmd(node, env, fd_in, fd_out);
		add_pid_to_list(env, pid);
	}
	else if (node->type == L_PARENTHESE)
	{
		pid = exec_pipe_subshell(node, env, fd_in, fd_out);
		add_pid_to_list(env, pid);
	}
}

int	exec_pipe_cmd(t_tree *node, t_env *env, int fd_in, int fd_out)
{
	int	pid;

	if (!node->n_value)
		return (0);
	domain_expand(node, env);
	pid = fork();
	if (pid < 0)
	{
		ft_free_all_malloc();
		free_env(&env);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
		close_extra_fds(node, fd_in, fd_out);
		if (redir_for_pipes(node, &fd_in, &fd_out) != 0)
		{
			free_env(&env);
			ft_free_all_malloc();
            exit(1);
		}
		if (command_is_empty(node))
		{
			free_env(&env);
			ft_free_all_malloc();
			close_pipe();
			exit (0);
		}
        if (builtin_pipe(node, env, &fd_in, &fd_out) == 44444)
            child_pipe(node, env, fd_in, fd_out);
        else
            exit(env->exit_status->exit_status);
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (126);
	}
	if (arg && arg[0] && !given_path(arg[0]))
		path = find_path(arg[0], paths, &env);
	else
		path = ft_strdup(arg[0]);
	if (fd_in != STDIN_FILENO)
		(dup2(fd_in, 0), close(fd_in));
	if (fd_out != STDOUT_FILENO)
		(dup2(fd_out, 1), close(fd_out));
	exec_pipe(path, paths, env_tab, arg);
}

void	exec_pipe(char *path, char **paths, char **env_tab, char **arg)
{
	(void)paths;
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

	status = 0;
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
	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->type == 6)
			return_value = (redir_in_pipe(tmp, fd_in));
		else if (tmp->type == 5 || tmp->type == 7)
			return_value = (redir_out_pipe(tmp, fd_out));
		else if (tmp->type == 4)
			return_value = heredoc_redir_pipe(node, fd_in);
		if (return_value != 0)
			return (return_value);
		tmp = tmp->next;
	}
	if (*fd_in != 0 && (dup2(*fd_in, STDIN_FILENO) == -1))
        return (1);
    if (*fd_out != 1 && (dup2(*fd_out, STDOUT_FILENO) == -1))
        return (1);
	else
		return (return_value);
}

int	heredoc_redir_pipe(t_tree *node, int *fd)
{
	if (node->fd_r < 0)
		return (1);
	if (*fd != STDIN_FILENO && *fd != node->fd_r)
		close(*fd);
	*fd = node->fd_r;
	return (0);
}

int redir_in_pipe(t_redir *redir, int *fd_in)
{
    struct stat st;
	char *path;
    path = strip_quotes_redir(redir->value);
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(redir->value, 2);
        ft_putendl_fd(": Is a directory", 2);
        return (1);
    }
    if (access(path, F_OK | R_OK) == -1)
    {
        perror(redir->value);
        return (1);
    }
    if (*fd_in != 0)
        close(*fd_in);
    *fd_in = open(path, O_RDONLY);
	if (*fd_in < 0)
		return (error_message(path));
    return (0);
}

int redir_out_pipe(t_redir *redir, int *fd_out)
{
    struct stat st;
	char	*path;
	
	path = strip_quotes_redir(redir->value);
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("minishell: Is a directory\n", 2);
        return (1);
    }
	if (*fd_out != 1)
    	close (*fd_out);
    if (redir->type == 5)
        *fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (redir->type == 7)
        *fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd_out < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(path);
        return (1); 
    }
    return (0);
}
