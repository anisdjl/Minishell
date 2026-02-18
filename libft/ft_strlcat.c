/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:21:27 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 16:01:36 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	y;
	size_t	a;

	y = 0;
	a = 0;
	while (dest[y])
	{
		y++;
	}
	if (size <= y)
		return (size + ft_strlen(src));
	while (src[a] && y + a < size - 1)
	{
		dest[a + y] = src[a];
		a++;
	}
	dest[a + y] = '\0';
	return (y + ft_strlen(src));
}

/*#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	//char dest[11] = "hello";
	//char *src = "world";
	
	printf("%zu\n", ft_strlcat("pqrstuvwxyz", "abcd", 1));
	printf("%zu\n", strlcat("pqrstuvwxyz", "abcd", 1));
	return 0;
}*/