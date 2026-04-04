/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:25:29 by anis              #+#    #+#             */
/*   Updated: 2026/04/04 11:57:10 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

/* ==================== builtin ================================ */

int		cd_command(t_tree *node, t_env *env);
int		pwd_command(t_tree *node, t_env *env);
int		env_command(t_tree *node, t_env **env);
int		echo_command(t_tree *node, t_env *env);
int		echo_command2(t_tree *node, t_env *env);
int		unset_command(t_tree *node, t_env **env);
void	unset_node(t_env **env, char *arg);
int		export_cmd(t_tree *node, t_env **env);
void	update_env(t_env *env, char *arg, char *splitted);
void	exit_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		pwd_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		cd_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		env_command_pipe(t_tree *node, t_env **env, int *fd_in, int *fd_out);
int		echo_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		echo_command2_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
int		unset_command_pipe(t_tree *node, t_env **env, int *fd_in, int *fd_out);
void	exit_non_numeric_pipes(char **arg, t_env *env);
int		env_command_for_export_pipe(t_tree *node, t_env **env, int *fd_in,
			int *fd_out);
int		export_pipe(t_tree *node, t_env **env, int *fd_in, int *fd_out);
void	numeric_exit_pipes(char **arg, char *nptr, t_env *env);
int		builtin_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out);
void	extract_oldpwd(t_value_node *n_value, t_env *env, char *new_value);
int		command_is_empty(t_tree *node);
int		echo_command_loop(char **arg, int y);
void	echo_command2_loop(char **arg, int y);
int		check_n(char *args);
void	exit_command(t_tree *node, t_env *env);
void	exit_non_numeric(char **arg, t_env *env, int *fd_in, int *fd_out);
int		non_numeric(char *arg);
void	numeric_exit(char **arg, char *nptr, t_env *env, int *fd_in,
			int *fd_out);
int		valid_export(char *args);
int		ft_lstsize_env(t_env *lst);
void	export_update_create(t_tree *node, t_env **env, int y);
void	create_new_node(t_env **env, char *arg);
int		go_to_home(t_tree *node, t_env *env, int *fd_in, int *fd_out,
			char *current_dir);
int		pwd_command_loop(t_env *tmp, void *ptr, char *current_dir);
int		return_to_old_pwd(t_tree *node, t_env *env, char *current_dir,
			int *fd_in, int *fd_out);

/* ==================== pipe ==================================== */

int		exec_pipe_cmd(t_tree *node, t_env *env, int fd_in, int fd_out);
void	child_pipe(t_tree *node, t_env *env, int fd_in, int fd_out);
void	exec_pipe(char *path, char **paths, char **env_tab, char **arg);
void	add_pid_to_list(t_env *env, int pid);
int		wait_all_pids(t_env *env);
t_pid	*ft_lstnew_pid(int content);
void	ft_lstadd_back_pid(t_pid **lst, t_pid *new);
int		redir_for_pipes(t_tree *node, int *fd_in, int *fd_out);
int		redir_in_pipe(t_redir *redir, int *fd_in);
int		redir_out_pipe(t_redir *redir, int *fd_out);
void	handle_pipes(t_tree *node, t_env *env, int fd_in, int fd_out);

/* ======================== exec ===================================== */

int		exec(t_tree *ast, t_env **env);
int		exec_cmd(t_tree *node, t_env **env);
char	**env_to_tab(t_env **env);
char	*find_path(char *cmd, char **env, t_env **envp);
int		exec_normal_command(t_tree *node, t_env *env);
int		given_path(char *cmd);
char	**get_paths(char **envp);
int		size_of_table(char **tab);
char	**args_to_tab(t_value_node *node_values);
int		subshell(t_tree *node, t_env *env);
int		ft_lstsize_arg(t_value_node *node_value);
int		child(t_tree *node, t_env *env);

/* ========================= redir ======================================*/

int		redir_function(t_tree *node);
int		redir_in(t_redir *redir);
int		redir_out(t_redir *redir);
void	save_fds(int *fd_in, int *fd_out);
void	reset_and_close(int *fd_in, int *fd_out);
int		env_command_for_export(t_tree *node, t_env **env);
int		check_existant(t_env *env, char *key);
char	*strip_quotes_redir(const char *src);
int		redir_is_directory(char *path);

/* ======================= heredoc ===================================== */

int		heredoc_redir_pipe(t_tree *node, int *fd_in);
char	*generate_herdoc_name(int index);
int		heredoc_redir(t_tree *node);
int		create_file(t_tree *node, t_env *env, t_redir *redir);
int		write_in_file(t_tree *node, t_env *env, t_redir *redir);
int	here_doc(t_tree *node, t_env *env);
int	pre_exec(t_tree *node, t_env *env);
int		error_message(char *path);
void	close_pipe(void);

#endif