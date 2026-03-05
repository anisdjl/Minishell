/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:03:31 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/05 16:45:58 by anis             ###   ########.fr       */
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
	key = malloc(sizeof(char) * y + 1);
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
		new = malloc(sizeof(t_env));
		new->key = create_key(envp[y]);
		new->value = ft_strchr(envp[y], '=');
		ft_lstadd_back_env(&env, new);
		y++;
	}
	return (env);
}
