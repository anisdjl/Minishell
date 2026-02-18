/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:22:50 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/18 18:12:20 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	y;
	size_t	a;

	y = 0;
	if (ft_strlen(little) < 1)
		return ((char *)big);
	while (big[y] && y < len)
	{
		a = 0;
		while (little[a] == big[y + a] && big[y + a] && y + a < len)
			a++;
		if (little[a] == '\0')
			return ((char *)(big + y));
		y++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	char str[] = "hello, my name is Eliott Alderson !";
	//char substr[0];
	//char *ptr = strnstr(str, substr, 30);
	char *ptr2 = ft_strnstr(str, str, 30);
	
	printf("%s\n", ptr2);
	//printf("%s",ptr);
	//printf("%s", strnstr(str, substr, 30));
	return (0);
}*/