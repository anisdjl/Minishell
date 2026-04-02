/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:39:17 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/02 17:55:01 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_command(t_tree *node, t_env *env)
{
	char	**arg;
	int		les;
	int		fd_in;
	int		fd_out;
	
	save_fds(&fd_in, &fd_out);
	if (redir_function(node))
		exit (1);
	les = env->exit_status->exit_status;
	wash_start(node->n_value);
	arg = args_to_tab(node->n_value);
	if (size_of_table(arg) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		reset_and_close(&fd_in, &fd_out);
		ft_free_all_malloc();
		free_env(&env);
		close_pipe();
		exit(les);
	}
	else if (size_of_table(arg) == 2 && !non_numeric(arg[1]))
		numeric_exit(arg, arg[1], env, &fd_in, &fd_out);
	else if (non_numeric(arg[1]))
		exit_non_numeric(arg, env, &fd_in, &fd_out);
	else if (size_of_table(arg) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		env->exit_status->exit_status = 1;
		reset_and_close(&fd_in, &fd_out);
	}
}

void	exit_non_numeric(char **arg, t_env *env, int *fd_in, int *fd_out)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_all_malloc();
	free_env(&env);
	close_pipe();
	exit(2);
}

void	numeric_exit(char **arg, char *nptr, t_env *env, int *fd_in, int *fd_out)
{
	int					y;
	long long			sign;
	unsigned long long	total;

	y = 0;
	sign = 1;
	total = 0;
	if (nptr[y] == '-' || nptr[y] == '+')
		if (nptr[y++] == '-')
			sign = -1;
	while (nptr[y] >= '0' && nptr[y] <= '9')
	{
		if (sign == 1 && (total > (unsigned long long)LLONG_MAX / 10
				|| (total == (unsigned long long)LLONG_MAX / 10
					&& (nptr[y] - '0') > (unsigned long long)LLONG_MAX % 10)))
			exit_non_numeric(arg, env, fd_in, fd_out);
		if (sign == -1 && (total > 9223372036854775808ULL / 10
				|| (total == 9223372036854775808ULL / 10
					&& (nptr[y] - '0') > 9223372036854775808ULL % 10)))
			exit_non_numeric(arg, env, fd_in, fd_out);
		total = total * 10 + (nptr[y++] - '0');
	}
	ft_putstr_fd("exit\n", 2);
	ft_free_all_malloc();
	free_env(&env);
	close_pipe();
	exit((unsigned char)(total * sign));
}

int	non_numeric(char *arg)
{
	int y;
	int	nb_operator;

	y = 0;
	if (arg[0] == '+' || arg[0] == '-')
		y++;
	while (arg[y])
	{
		if (!ft_isdigit(arg[y]))
			return (1);
		y++;
	}
	return (0);
}
