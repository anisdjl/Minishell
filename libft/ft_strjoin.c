/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:34:51 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/28 22:18:36 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		y;
	char	*new_str;

	a = 0;
	y = 0;
	new_str = ft_malloc(1, sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	while (s1[a])
	{
		new_str[y] = s1[a];
		a++;
		y++;
	}
	a = 0;
	while (s2[a])
	{
		new_str[y] = s2[a];
		a++;
		y++;
	}
	new_str[y] = '\0';
	return (new_str);
}

/*#include <stdio.h>

int main(void)
{
	char s1[] = "my name is ";
	char s2[] = "Eliott Alderson";
	
	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/