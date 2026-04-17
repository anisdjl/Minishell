/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:50:51 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/17 15:22:41 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	if (!env || !*env)
		return ;
	tmp = (*env);
	free(tmp->exit_status);
	free_pid(&(*env)->pid);
	while (tmp)
	{
		next = tmp->next;
		tmp->next = NULL;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	(*env) = NULL;
}

void	free_pid(t_pid **pid)
{
	t_pid	*tmp;
	t_pid	*next;

	if (!pid || !*pid)
		return ;
	tmp = (*pid);
	while (tmp)
	{
		next = tmp->next;
		tmp->next = NULL;
		free(tmp);
		tmp = next;
	}
	(*pid) = NULL;
}

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	int		a;
	int		y;
	char	*new_str;

	a = 0;
	y = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	while (s1[a])
	{
		new_str[y] = s1[a];
		a++;
		y++;
	}
	a = 0;
	while (s2[a])
	{
		new_str[y] = s2[a];
		a++;
		y++;
	}
	new_str[y] = '\0';
	return (new_str);
}

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
			ptr = ptr->next;
		ptr->next = new_env;
	}
}

t_env	*manual_env(void)
{
	t_env		*env;

	env = NULL;
	manual_env2(&env);
	env->exit_status = malloc(sizeof(t_exit_status) * 1);
	env->exit_status->exit_status = 0;
	env->pid = NULL;
	return (env);
}
