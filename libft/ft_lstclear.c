/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:10:59 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/19 16:14:24 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstclear(t_token **lst, void (*del)(void *))
// {
// 	t_list	*temp;

// 	if (!del || !lst)
// 		return ;
// 	temp = *lst;
// 	while (temp)
// 	{
// 		temp = temp->next;
// 		del((*lst)->content);
// 		free (*lst);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// }
