/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:43:34 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/26 17:13:20 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;	
}	t_env;

void	ft_lstadd_back_env(t_env **lst, t_env *new_env);
int 	get_env(char **envp);
char	*create_key(char *envp);

#endif