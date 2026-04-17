/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:07:44 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/17 15:22:28 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	manual_env2(t_env **env)
{
	t_env		*new;
	char		**manual_envp;
	int			y;
	char		*current_dir;

	y = 0;
	new = NULL;
	current_dir = NULL;
	manual_envp = ft_malloc(1, sizeof(char *) * 4);
	manual_envp[0] = ft_strjoin("PWD=", getcwd(current_dir, 4096));
	manual_envp[1] = ft_strdup("SHLVL=1");
	manual_envp[2] = ft_strdup("_=/usr/bin/env");
	manual_envp[3] = NULL;
	while (manual_envp[y])
	{
		new = malloc(sizeof(t_env));
		if (!new)
		{
			ft_free_all_malloc();
			free_env(env);
			exit(EXIT_FAILURE);
		}
		fill_env(manual_envp, y, new, env);
		y++;
	}
}
