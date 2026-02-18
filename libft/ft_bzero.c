/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:21:41 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/06 11:41:50 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	y;

	y = 0;
	while (y < n)
	{
		*(unsigned char *)(s + y) = '\0';
		y++;
	}
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s1[20];
	char s2[20];

	ft_bzero(s1, 10);
	bzero(s2, 10);
	printf("%s", s1);
	printf("%s", s2);
	return (0);
}*/