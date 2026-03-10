/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:24:08 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/10 14:02:07 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	y;

	y = 0;
	while (s[y])
	{
		if (s[y] == (char)c)
			return ((char *)(s + y));
		else
			y++;
	}
	if (s[y] == (char)c)
		return ((char *)(s + y));
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char str[] = "hello world";
	
// 	printf("%s\n", ft_strchr	(str, 'l'));
// 	printf("%s", strchr(str, 'l'));
// 	return (0);
// }