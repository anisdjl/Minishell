/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:44:57 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 17:59:05 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	y;

	y = 0;
	if (n == 0)
		return (0);
	while (y < n)
	{
		if (*(const char *)(s1 + y) != *(const char *)(s2 + y))
			return (*(unsigned char *)(s1 + y) - *(unsigned char *)(s2 + y));
		else
			y++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// 
// int	main(void)
// {
	// char s[] = {'h', 'e', 'o', 'l', 'o'};
	// char t[] = {'h', 'e', 'l', 'l', 'o'};
	// 
	// printf("%d\n", ft_memcmp(s, t, 0));
	// printf("%d", memcmp(s, t, 0));
	// return (0);
// }