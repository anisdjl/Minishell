/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:43:34 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/02 11:57:09 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				ft_lstadd_back_env(t_env **lst, t_env *new_env);
t_env				*get_env(char **envp);
char				*create_key(char *envp);

#endif