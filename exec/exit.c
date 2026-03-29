/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volt <volt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:39:17 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/29 18:00:52 by volt             ###   ########.fr       */
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
		ft_free_all_malloc();
		free_env(&env);
		exit(les);
	}
	else if (size_of_table(arg) == 2 && !non_numeric(arg[1]))
		numeric_exit(arg, arg[1], env);
	else if (non_numeric(arg[1]))
		exit_non_numeric(arg, env);
	else if (size_of_table(arg) > 2)
	{
		//ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: too many arguments\n", 2); //ft_putstr_fd("minishell: exit: too many arguments\n", 2)
		env->exit_status->exit_status = 1;
		reset_and_close(&fd_in, &fd_out);
	}
}

void	exit_non_numeric(char **arg, t_env *env)
{
	//ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell ", 2); // ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_all_malloc();
	free_env(&env);
	exit(2);
}

void	numeric_exit(char **arg, char *nptr, t_env *env)
{
	int	y;
	int	sign;
	long long	total;
	int			digit;

	total = 0;
	sign = 1;
	y = 0;
	if (nptr[y] == '-' || nptr[y] == '+')
	{
		if (nptr[y] == '-')
			sign = -sign;
		y++;
	}
	while (nptr[y] >= '0' && nptr[y] <= '9')
	{
		digit = nptr[y] - '0';
        if (sign == 1 && (total > (LLONG_MAX - digit) / 10))
            exit_non_numeric(arg, env);
        if (sign == -1 && (total > (-(LLONG_MIN + digit)) / 10))
			exit_non_numeric(arg, env);
		total = total * 10 + nptr[y] - '0';
		y++;
	}
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
