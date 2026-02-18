/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:37:24 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/10 17:17:14 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	y;

	y = 0;
	while (y < n)
	{
		*(unsigned char *)(s + y) = (unsigned char)c;
		y++;
	}
	return (s);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s1[100] = "hello worldttt";
	char s2[100] = "hello worldttt";
	
	size_t size = 10;

	ft_memset(s1, 'r', size);
	memset(s2, 'r', 10);
	printf("%s\n", s1);
	printf("%s\n", s2);
	return (0);
}*/