/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:57:25 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 15:22:40 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	y;
	size_t	a;

	y = 0;
	while (src[y])
		y++;
	if (n == 0)
		return (y);
	a = 0;
	while (a < n - 1 && src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (y);
}

/*#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	char dest[6] = "hi";
	char *src = "world";

	printf("%zu\n", ft_strlcpy(dest, src, 10));
	printf("%zu\n", strlcpy(dest, src, 10));
	printf("%s", dest);
	return (0);
}*/