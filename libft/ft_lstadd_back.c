/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:48:53 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/19 13:56:00 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

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
