/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:43:23 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 14:46:44 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	y;

	if (!dest && !src)
		return (NULL);
	y = 0;
	while (y < n)
	{
		*(char *)(dest + y) = *(const char *)(src + y);
		y++;
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>
 
int main(void)
{
	char *s = (void *)0;
	char *t = (void *)0;
	char *a = (void *)0;
	//ft_memcpy(((void*)0), ((void*)0), 3);
	memcpy(0, 0, 3);
	printf("%s\n", a);
	//printf("%s", s);
	return (0);
}*/