/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:03:15 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/17 15:00:02 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	y;

	y = 0;
	if (!src && !dest)
		return (NULL);
	if (dest > src)
	{
		while (n > 0)
		{
			*(unsigned char *)(dest + n - 1)
				= *(const unsigned char *)(src + n - 1);
			n--;
		}
	}
	else
	{
		while (y < n)
		{
			*(unsigned char *)(dest + y) = *(unsigned const char *)(src + y);
			y++;
		}
	}
	return (dest);
}
