/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:03:31 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 12:56:46 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_key(char *envp)
{
	int		y;
	char	*key;

	y = 0;
	while (envp[y] && envp[y] != '=')
		y++;
	key = malloc(sizeof(char) * (y + 1));
	if (!key)
	{
		ft_free_all_malloc();
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (envp[y] && envp[y] != '=')
	{
		key[y] = envp[y];
		y++;
	}
	key[y] = '\0';
	return (key);
}

char	*ft_strdup_env(const char *s)
{
	char	*new_str;
	int		a;

	a = 0;
	while (s[a])
		a++;
	new_str = malloc(sizeof(char) * a + 1);
	if (!new_str)
		return (NULL);
	a = 0;
	while (s[a])
	{
		new_str[a] = s[a];
		a++;
	}
	new_str[a] = '\0';
	return (new_str);
}

t_env	*get_env(char **envp)
{
	int		y;
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
			free_env(&env);
			exit(EXIT_FAILURE);
		}
		fill_env(envp, y, new, &env);
		y++;
	}
	env->exit_status = malloc(sizeof(t_exit_status) * 1);
	env->exit_status->exit_status = 0;
	env->pid = NULL;
	return (env);
}

void	fill_env(char **envp, int y, t_env *new, t_env **env)
{
	void	*ptr;

	new->next = NULL;
	new->exit_status = NULL;
	new->pid = NULL;
	new->key = create_key(envp[y]);
	ptr = ft_strchr(envp[y], '=');
	if (ptr)
		new->value = ft_strdup_env(ptr);
	else
		new->value = NULL;
	ft_lstadd_back_env(env, new);
}

int	env_command_for_export(t_tree *node, t_env **env)
{
	t_env	*tmp;
	int		fd_in;
	int		fd_out;

	if (!env || !*env)
		return (0);
	save_fds(&fd_in, &fd_out);
	redir_function(node);
	tmp = *env;
	while (tmp)
	{
		if (tmp->key && ft_strlen(tmp->key) > 0
			&& tmp->value && ft_strlen(tmp->value) > 0)
			printf("export %s%s\n", tmp->key, tmp->value);
		else
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
	reset_and_close(&fd_in, &fd_out);
	return (0);
}
