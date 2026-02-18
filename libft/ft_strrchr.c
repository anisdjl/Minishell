/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:20:15 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 17:25:57 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	y;

	y = 0;
	while (s[y])
	{
		y++;
	}
	while (y >= 0)
	{
		if (s[y] == (char)c)
		{
			return ((char *)(s + y));
		}
		else
			y--;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "hello world";
	
	printf("%s\n", ft_strrchr(str, 'l'));
	printf("%s", strrchr(str, 'l'));
	return (0);
}*/