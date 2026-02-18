/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:54:25 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/18 16:14:24 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	size_t	y;

	if (!f)
		return (NULL);
	y = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (NULL);
	while (s[y])
	{
		new_str[y] = f(y, s[y]);
		y++;
	}
	new_str[y] = '\0';
	return (new_str);
}

/*#include <stdio.h>

int	main(void)
{
	char str[] = "hello world";
	char (*f)(unsigned int, char) = &replace;
	
	printf("%s", ft_strmapi(str, f));
	return (0);
}

char	replace(unsigned int y, char c)
{
	if (y > 0 && y < 5)
		return ('i');
	else
		return (c);
}*/