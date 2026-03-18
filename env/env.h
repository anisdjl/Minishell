/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:43:34 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/18 17:21:20 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

typedef struct s_exit_status
{
	int	exit_status;
}	t_exit_status;

typedef	struct s_pid
{
	int	pid;
	struct s_pid *next;
}	t_pid;

typedef struct s_env
{
	char			*key;
	char			*value;
	int 			fd_r;
	int 			fd_w;
	struct s_env	*next;
	t_exit_status	*exit_status;
	t_pid			*pid;
}					t_env;

typedef struct	s_here_doc
{
	int	fd_write;
	int	fd_read;
}	t_here_doc;

void	ft_lstadd_back_env(t_env **lst, t_env *new_env);
t_env 	*get_env(char **envp);
char	*create_key(char *envp);
int		env_command_for_export(t_tree *node, t_env **env);
char	*ft_strdup_env(const char *s);
void	free_env(t_env **env);
void	free_pid(t_pid **pid);

#endif