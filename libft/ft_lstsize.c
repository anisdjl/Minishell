/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:53:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/19 13:57:26 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_token *lst)
{
	int	y;

	y = 0;
	while (lst)
	{
		lst = lst->next;
		y++;
	}
	return (y);
}

/*#include <stdio.h>

int main(void)
{
	t_list *head;
	
	head = malloc(sizeof(t_list));
	if (!head)
		return (0);
	head->content = 0;
	head->next = NULL;
	printf("%d", ft_lstsize(head));
	free (head);
	return (0);
}*/