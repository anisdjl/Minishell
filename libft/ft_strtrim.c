/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:45 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/18 15:50:40 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	y;

	y = 0;
	while (set[y])
	{
		if (set[y] == c)
			return (1);
		else
			y++;
	}
	return (0);
}

static void	ft_create_newstr(const char *s1, char *new_str, int i, int j)
{
	int	y;

	y = 0;
	while (i <= j)
	{
		new_str[y] = s1[i];
		i++;
		y++;
	}
	new_str[y] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*new_str;

	j = 0;
	i = 0;
	while (s1[i] && is_set(s1[i], set) == 1)
	{
		i++;
	}
	while (s1[j])
		j++;
	j = j - 1;
	while (is_set(s1[j], set) == 1 && j > 0)
		j--;
	if (i > j)
		return (ft_strdup(""));
	new_str = malloc(sizeof(char) * (j - i + 1) + 1);
	if (!new_str)
		return (0);
	ft_create_newstr(s1, new_str, i, j);
	return (new_str);
}

/*#include <stdio.h>

int	main(void)
{
	char s1[] = "           \n";
	char set[] = "hello hru today";
	
	printf("%s", ft_strtrim(s1, set));
	return (0);
}*/