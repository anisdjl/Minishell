/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:09:28 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/18 09:52:36 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	y;
	int	sign;
	int	total;

	total = 0;
	sign = 1;
	y = 0;
	while ((nptr[y] >= 9 && nptr[y] <= 13) || nptr[y] == 32)
		y++;
	if (nptr[y] == '-')
	{
		sign = -sign;
		y++;
	}
	else if (nptr[y] == '+')
		y++;
	while (nptr[y] >= '0' && nptr[y] <= '9')
	{
		total = total * 10 + nptr[y] - '0';
		y++;
	}
	return (total * sign);
}

/*#include <stdio.h>

int	main(void)
{
	const char s[] = "-12457abcdef";
	printf("%d", ft_atoi(s));
	return (0);
}*/
