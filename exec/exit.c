/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:39:17 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/10 15:18:25 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_command(t_tree *node, t_env *env)
{
	char	**arg;

	arg = args_to_tab(node->n_value);
	if (size_of_table(arg) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(env->exit_status->exit_status);
	}
	else if (size_of_table(arg == 2 && !non_numeric(arg[1])))
		numeric_exit(node, env);
	else if (non_numeric(arg[1]))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else if (size_of_table(arg) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		env->exit_status->exit_status = 1;
	}
	
}

int	