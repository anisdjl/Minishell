/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:41:11 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/18 10:53:26 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../main.h"

// static void	strcpy_(char *dst, const char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// }

// char	*ft_strdup(char *s)
// {
// 	char	*new;

// 	new = malloc((ft_strlen(s) + 1) * sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	strcpy_(new, s);
// 	return (new);
// }
/*
#include <stdio.h>

int	main(void)
{
	char	*s;
	char	*s2;

	s = "hello world ! ! ! !";
	s2 = ft_strdup(s);
	printf("duplication s = : %s\n", s2);
	free(s2);
	return (0);
}
*/
