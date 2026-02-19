/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:44:06 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/19 13:59:46 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_token	*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_token	*new_node;
// 	t_token	*newlist;
// 	void 	*contentf;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	newlist = NULL;
// 	while (lst)
// 	{
// 		contentf = f(lst->content);
// 		new_node = ft_lstnew(contentf);
// 		if (!new_node)
// 		{
// 			del(contentf);
// 			ft_lstclear(&newlist, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&newlist, new_node);
// 		lst = lst->next;
// 	}
// 	return (newlist);
// }
