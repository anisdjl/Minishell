/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:34:58 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/19 16:16:32 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	y;

	y = 0;
	while (s[y])
		y++;
	return (y);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char s[] = "hello";
	printf("%zu\n", ft_strlen(s));
	printf("%lu", strlen(s));
	return (0);
}*/