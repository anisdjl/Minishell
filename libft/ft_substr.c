/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:07:03 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/18 14:58:00 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t n1, size_t n2)
{
	if (n1 <= n2)
		return (n1);
	return (n2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	y;
	int		a;
	char	*str;

	y = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = malloc((min(len, ft_strlen(s) - start) + 1));
	if (!str)
		return (NULL);
	a = start;
	while (y < len && s[a])
	{
		str[y] = s[a];
		y++;
		a++;
	}
	str[y] = '\0';
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	char s[20] = "";
	
	printf("%s", ft_substr(s, 21, 14));
	return (0);
}*/