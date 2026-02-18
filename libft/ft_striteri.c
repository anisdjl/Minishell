/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:31:26 by adjelili          #+#    #+#             */
/*   Updated: 2025/11/15 14:26:28 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	y;

	if (!f || !s)
		return ;
	y = 0;
	while (s[y])
	{
		f(y, (s + y));
		y++;
	}
}

/*#include <stdio.h>

int	main(void)
{
	char str[] = "hello world";
	void (*f)(unsigned int, char *) = &replace;
	
	ft_striteri(str, f);
	printf("%s", str);
	return (0);
}
void	replace(unsigned int y, char* c)
{
	if (y > 0 && y < 5)
		c = 'i';
}*/