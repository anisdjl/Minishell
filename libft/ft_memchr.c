/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:40:38 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 17:55:24 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	y;

	y = 0;
	while (y < n)
	{
		if (*(char *)(s + y) == (char)c)
			return ((char *)(s + y));
		else
			y++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char membloc[] = {'h', 'e', 'l', 'l', 'o'};
	char *p = memchr(membloc, 'a', 4);
	char *t = ft_memchr(membloc, 'a', 4);
	
	printf("%c\n", t[2]);
	printf("%c", p[2]);
	return (0);
}*/