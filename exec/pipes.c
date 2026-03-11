/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:29:52 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/11 16:40:08 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pipes(t_tree *node, t_env *env)
{
	int	last_fd;
	int	pipe_fd;
	int	pid;
	t_pid	*pid_new;

	env->pid = NULL;
	last_fd = 0;
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe: ");
		ft_free_all_malloc(); // + free_env
		exit(127);
	}
	if ((pid = fork()) < 0)
	{
		perror("fork: ");
		ft_free_all_malloc(); // + free_env
		exit(127);
	}
	pid_new = ft_lstnew_pid(pid);
	ft_lstadd_back_pid(&env->pid, pid_new);
	if (pid == 0)
	{

	}
}

t_pid	*ft_lstnew_pid(void *content)
{
	t_pid	*new_node;

	new_node = malloc(sizeof(t_pid));
	if (!new_node)
		return (NULL);
	new_node->pid = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_pid(t_pid **lst, t_pid *new)
{
	t_pid	*ptr;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		ptr = *lst;
		while (ptr->next)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}
