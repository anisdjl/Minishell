/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:25:29 by anis              #+#    #+#             */
/*   Updated: 2026/04/07 16:31:06 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_tree t_tree;
typedef struct s_env  t_env;
typedef struct s_redir t_redir;
typedef struct s_value_node t_value_node;

/* ======================== exec ===================================== */

/* main function */

int		exec(t_tree *ast, t_env **env);
int		exec_cmd(t_tree *node, t_env **env);
int		exec_normal_command(t_tree *node, t_env *env);
int		subshell(t_tree *node, t_env *env);
void	child(t_tree *node, t_env *env);
void	exec_pipe_subshell2(t_tree *node, t_env *env, int *fd_in, int *fd_out);
void	check_empty_redirs(t_tree *node, t_env *env, int *fd_in, int *fd_out);
void	exit_wrong_pid(t_env *env);

/* path */

char	*find_path(char *cmd, char **env, t_env **envp);
int		given_path(char *cmd);
char	**get_paths(char **envp);

/* tab/arg */

char	**env_to_tab(t_env **env);
int		size_of_table(char **tab);
char	**args_to_tab(t_value_node *node_values);
int		ft_lstsize_arg(t_value_node *node_value);

/* error */

void	error_execve(char **arg, t_env *env);
void	child_exit_status(int status, t_env *env, int pid);
void	exit_no_path(char *cmd, t_env **envp);
void	exit_classic(t_env *env, t_tree *node, int les);

/* empty check */

int		command_is_empty(t_tree *node);
int		empty_check(t_tree *node);

/* ======================= heredoc ===================================== */

/* main function */

int		heredoc_redir_pipe(t_tree *node, int *fd_in);
int		heredoc_redir(t_tree *node);
char	*generate_herdoc_name(int index);
int		create_file(t_tree *node, t_env *env, t_redir *redir);
int		here_doc(t_tree *node, t_env *env);

/* idk */

int		pre_exec(t_tree *node, t_env *env);
int		error_message(char *path);
void	close_pipe(void);
void	close_extra_fds(t_tree *node, int fd_in, int fd_out);
int		exec_pipe_subshell(t_tree *node, t_env *env, int fd_in, int fd_out);

/* redir utils */

void	save_fds(int *fd_in, int *fd_out);
void	reset_and_close(int *fd_in, int *fd_out);

/* write */

int		write_in_file_lp1(char *line, t_redir *redir, t_env *env);
int		write_in_file_check(char *line, t_redir *redir, t_env *env);
int		write_in_file(t_tree *node, t_env *env, t_redir *redir);

/* echo/pwd */

int		echo_cmd_pipe_loop(char **arg, int y);
int		echo_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		echo_command2_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		pwd_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		pwd_cmd_pipe_loop(t_env *tmp);

#endif