/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:03:31 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/06 16:25:45 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new_env)
{
	t_env	*ptr;

	ptr = NULL;
	if (*lst == NULL)
		*lst = new_env;
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
	int 	y;
	char	*key;

	y = 0;
	while (envp[y] != '=')
		y++;
	key = malloc(sizeof(char) * (y + 1));
	if (!key)
	{
		ft_free_all_malloc();
		//ft_free_env();
		exit(EXIT_FAILURE);
	}
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
	new = NULL;
	y = 0;
	while (envp[y])
	{
		new = malloc(sizeof(t_env));
		if (!new)
		{
			ft_free_all_malloc();
			//ft_free_env();
			exit(EXIT_FAILURE);
		}
		new->next = NULL;
		new->key = create_key(envp[y]);
		new->value = ft_strchr(envp[y], '=');
		ft_lstadd_back_env(&env, new);
		y++;
	}
	return (env);
}

// void	free_env(t_env **env) elle ne marche pas
// {
// 	t_env	*current;
// 	t_env	*next;

// 	if (!env || !*env)
// 		return ;
// 	current = *env;
// 	next = NULL;
// 	while (current)
// 	{
// 		if (current->next)
// 			next = current->next;
// 		free(current);
// 		if (next)
// 			current = next;
// 		else
// 			return ;
// 	}
// }

