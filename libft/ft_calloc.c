/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:14:19 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/21 10:25:45 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	y;
	char	*ptr;

	if (nmemb != 0 && size >= (SIZE_MAX - 1) / nmemb)
		return (NULL);
	y = 0;
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	while (y < nmemb * size)
	{
		ptr[y] = 0;
		y++;
	}
	return (ptr);
}

/*#include <stdio.h>

int main(void)
{
	ft_calloc(4, 4);
	calloc(4, 4);
}*/