/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:03:31 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/27 15:27:49 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new_env)
{
	t_env	*ptr;

	if (*lst == NULL)
	{
		*lst = new_env;
	}
	else
	{
		ptr = *lst;
		while (ptr->next)
		{
			ptr = ptr->next;
		}
		ptr->next = new_env;
	}
}

char	*create_key(char *envp)
{
	int y;
	char	*key;

	y = 0;
	while (envp[y] != '=')
		y++;
	key = ft_malloc(1, sizeof(char) * y + 1);
	y = 0;
	while (envp[y] != '=')
	{
		key[y] = envp[y];
		y++;
	}
	key[y] = '\0';
	return (key);
}

t_env *get_env(char **envp)
{
	int y;
	t_env	*env;
	t_env	*new;
	
	env = NULL;
	y = 0;
	while (envp[y])
	{
		new = ft_malloc(1, sizeof(t_env));
		new->key = create_key(envp[y]);
		new->value = ft_strchr(envp[y], '=');
		ft_lstadd_back_env(&env, new);
		y++;
	}
	
	// new = env;
	// while(new)
	// {
	// 	printf("%s%s\n", new->key, new->value);
	// 	new = new->next;
	// }
	return (env);
}
