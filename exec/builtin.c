/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:54:04 by anis              #+#    #+#             */
/*   Updated: 2026/03/03 18:27:19 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_command(t_tree *node, t_env *env)
{
	char	current_dir[100];

	getcwd(current_dir, 100); // peut etre elle qui fait des leaks ??
	if (chdir(node->arg[1]) != 0)
	{
		ft_putstr_fd(node->arg[0], 2);
		write(2, ": ", 2);
		perror(node->arg[1]);
		return (1);
	}
	return (0);
}

int pwd_command(t_tree *node, t_env *env)
{
	char	current_dir[1096];

	if (!getcwd(current_dir, 1096))
	{
		perror(current_dir);
		return (1);
	}
	else
		printf("%s\n", current_dir);
	return (0);
}

int	env_command(t_tree *node)
{
	t_tree *tmp;

	
}
