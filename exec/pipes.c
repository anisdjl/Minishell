/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:29:52 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/11 15:03:52 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int	handle_pipes(t_tree *node, t_env *env)
// {
// 	int	pipe_fd[2];
// 	int	pid;
// 	int

// 	if (pipe(pipe_fd) == -1);
// 	{
// 		ft_free_all_malloc();
// 		exit(EXIT_FAILURE); // ou relancer minishell ?
// 	}
// 	pid = fork();
// 	(close(pipe_fd[0]), close(pipe_fd[1]));
// 	if (pid < 0)
// 	{
// 		ft_free_all_malloc();
// 		exit(EXIT_FAILURE); // ou relancer minishell
// 	}
// 	if (pid == 0)
// 	{
// 		if (node->type == )
// 		dup2(pipe_fd[1], )
// 		exec(node->left, env);
// 	}
// 	// wait_for_childrens
// }
