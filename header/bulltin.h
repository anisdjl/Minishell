/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:47:39 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/04 15:40:25 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BULLTIN_H
# define BULLTIN_H

# include "../minishell.h"

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
int		go_to_home(t_tree *node, t_env *env, char *current_dir);
int		pwd_command_loop(t_env *tmp, void *ptr, char *current_dir);
int		return_to_old_pwd(t_tree *node, t_env *env, char *current_dir);
int		go_to_home_pipe(t_tree *node, t_env *env, char *current_dir);
void	extract_oldpwd_pipe(t_value_node *n_value, t_env *env, char *new_value);
int	return_to_old_pwd_pipe(t_tree *node, t_env *env, char *current_dir);

#endif