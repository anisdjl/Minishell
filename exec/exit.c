/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:39:17 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/10 16:10:18 by adjelili         ###   ########.fr       */
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
int	numeric_exit(char **arg, t_env *env)
{
	long long	y;

	y = 0;
	while
}

int	non_numeric(char *arg)
{
	int y;

	y = 0;
	while (arg[y])
	{
		if (!ft_isdigit(arg[y]))
			return (1);
		y++;
	}
	return (0);
}

int	ft_atoll(const char *nptr)
{
	int	y;
	int	sign;
	int	total;

	total = 0;
	sign = 1;
	y = 0;
	while ((nptr[y] >= 9 && nptr[y] <= 13) || nptr[y] == 32)
		y++;
	if (nptr[y] == '-')
	{
		sign = -sign;
		y++;
	}
	else if (nptr[y] == '+')
		y++;
	while (nptr[y] >= '0' && nptr[y] <= '9')
	{
		total = total * 10 + nptr[y] - '0';
		y++;
	}
	return (total * sign);
}
