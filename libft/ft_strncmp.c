/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:04:08 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 17:30:46 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	y;

	y = 0;
	while ((s1[y] || s2[y]) && y < n)
	{
		if (s1[y] != s2[y])
			return ((unsigned char)(s1[y]) - (unsigned char)(s2[y]));
		else
			y++;
	}
	return (0);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s[] = "hello friend !";
	char t[] = "hello world";
	
	printf("%d\n", ft_strncmp(s, t, 6));
	printf("%d", strncmp(s, t, 6));
	return (0);
}*/