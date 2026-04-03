/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butltin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 19:10:46 by eprieur           #+#    #+#             */
/*   Updated: 2026/04/03 19:10:47 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	echo_command_loop(char **arg, int y)
{
	while (arg[y] && !check_n(arg[y]))
		y++;
	if (y == size_of_table(arg))
		return (0);
	while (arg[y])
	{
		ft_putstr_fd(arg[y], 1);
		if (y < size_of_table(arg) - 1)
			ft_putchar_fd(' ', 1);
		y++;
	}
	return (1);
}

int	pwd_command_loop(t_env *tmp, void *ptr, char *current_dir)
{
	if (ptr)
		printf("%s\n", current_dir);
	else if (!ptr)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->key, "PWD", 3) == 0 && ft_strlen(tmp->key) == 3)
			{
				printf("%s\n", tmp->value + 1);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}

void	echo_command2_loop(char **arg, int y)
{
	while (arg[y])
	{
		ft_putstr_fd(arg[y], 1);
		if (y < size_of_table(arg) - 1)
			ft_putchar_fd(' ', 1);
		y++;
	}
}
