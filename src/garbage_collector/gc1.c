/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:09:48 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 16:24:30 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_list	**return_adress(void)
{
	static t_list	*list = NULL;

	return (&list);
}

void	ft_free_all_malloc(void)
{
	t_list	**list_ptr;
	t_list	*tmp;
	t_list	*next;

	list_ptr = return_adress();
	if (!list_ptr || !*list_ptr)
		return ;
	tmp = (*list_ptr);
	while (tmp)
	{
		next = tmp->next;
		tmp->next = NULL;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = next;
	}
	(*list_ptr) = NULL;
}

void	ft_free_malloc(void *ptr)
{
	t_list	**head;
	t_list	*prev;
	t_list	*current;

	head = return_adress();
	current = (*head);
	prev = NULL;
	while (current)
	{
		if (current->content == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->content);
			free(current);
		}
		prev = current;
		current = current->next;
	}
}

void	*ft_malloc(size_t nmemb, size_t size)
{
	t_list	**list_ptr;
	t_list	*new;
	void	*ptr;

	list_ptr = return_adress();
	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		ft_free_all_malloc();
	new = ft_lstnew_gc(ptr);
	if (!new)
		ft_free_all_malloc();
	ft_lstadd_back_gc(list_ptr, new);
	return (ptr);
}

// void	*ft_calloc_gc(size_t nmemb, size_t size)
// {
// 	size_t	y;
// 	char	*ptr;

// 	if (nmemb != 0 && size >= (SIZE_MAX - 1) / nmemb)
// 		return (NULL);
// 	y = 0;
// 	ptr = malloc(size * nmemb);
// 	if (!ptr)
// 		return (NULL);
// 	while (y < nmemb * size)
// 	{
// 		ptr[y] = 0;
// 		y++;
// 	}
// 	return (ptr);
// }
