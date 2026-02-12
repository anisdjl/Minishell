/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:47:48 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/12 13:21:06 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_tree	*ft_lstnew(int content)
{
	t_tree	*lst;

	lst = malloc(sizeof(t_tree));
	if (lst == NULL)
		return (NULL);
	lst->right = NULL;
	lst->left = NULL;
	return (lst);
}

/*
int	main(void)
{
	int	nb;

	nb = 42;
	ft_lstnew(&nb);
	return (0);
}
*/