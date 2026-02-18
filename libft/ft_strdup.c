/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:22:47 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/18 09:54:50 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		a;

	a = 0;
	while (s[a])
		a++;
	new_str = malloc(sizeof(char) * a + 1);
	if (!new_str)
		return (0);
	a = 0;
	while (s[a])
	{
		new_str[a] = s[a];
		a++;
	}
	new_str[a] = '\0';
	return (new_str);
}

/*#include <stdio.h>

int	main(void)
{
	char s[] = "hello world";

	printf("%s", ft_strdup(s));
	return (0);
}*/