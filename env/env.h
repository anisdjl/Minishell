/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:43:34 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/12 17:48:51 by eprieur          ###   ########.fr       */
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
	struct s_env	*next;
	t_exit_status	*exit_status;
	t_pid	*pid;
}					t_env;

void	ft_lstadd_back_env(t_env **lst, t_env *new_env);
t_env 	*get_env(char **envp);
char	*create_key(char *envp);
int		env_command_for_export(t_tree *node, t_env **env);
char	*ft_strdup_env(const char *s);
//void	free_env(t_env **env);

#endif