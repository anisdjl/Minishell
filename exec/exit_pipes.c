/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:43:09 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/04 16:00:09 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_command_pipe(t_tree *node, t_env *env, int *fd_in, int *fd_out)
{
	char	**arg;
	int		les;

	les = env->exit_status->exit_status;
	arg = args_to_tab(node->n_value);
	if (redir_for_pipes(node, fd_in, fd_out))
		exit(1);
	if (size_of_table(arg) == 1)
	{
		ft_free_all_malloc();
		free_env(&env);
		close_pipe();
		exit(les);
	}
	else if (size_of_table(arg) == 2 && !non_numeric(arg[1]))
		numeric_exit_pipes(arg, arg[1], env);
	else if (non_numeric(arg[1]))
		exit_non_numeric_pipes(arg, env);
	else if (size_of_table(arg) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free_env(&env);
		ft_free_all_malloc();
		close_pipe();
		exit (146);
	}
}

void	exit_non_numeric_pipes(char **arg, t_env *env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_all_malloc();
	free_env(&env);
	close_pipe();
	exit(2);
}

void	numeric_exit_pipes(char **arg, char *nptr, t_env *env)
{
	int	y;
	int	sign;
	unsigned long long	total;
	int			digit;

	total = 0;
	sign = 1;
	y = 0;
	if (nptr[y] == '-')
		sign = -sign;
	y++;
	while (nptr[y] >= '0' && nptr[y] <= '9')
	{
		digit = nptr[y] - '0';
        if (sign == 1 && (total > (unsigned long long)LLONG_MAX / 10
				|| (((total == (unsigned long long)LLONG_MAX / 10
					&& ((unsigned long long)(nptr[y] - '0') > (unsigned long long)LLONG_MAX % 10))))))
            exit_non_numeric_pipes(arg, env);
        if (sign == -1 && (total > 9223372036854775808ULL / 10
				|| (((total == 9223372036854775808ULL / 10
					&& ((unsigned long long)(nptr[y] - '0') > 9223372036854775808ULL % 10))))))
			exit_non_numeric_pipes(arg, env);
		total = total * 10 + nptr[y] - '0';
		y++;
	}
	free_env(&env);
	close_pipe();
	ft_free_all_malloc();
	exit((unsigned char)(total * sign));
}
