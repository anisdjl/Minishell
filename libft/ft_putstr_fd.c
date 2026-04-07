/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:23:24 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/04 16:24:05 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	y;

	y = 0;
	while (s[y])
	{
		ft_putchar_fd(s[y], fd);
		y++;
	}
}

/*int main(void)
{
	char str[] = "hello world";

	ft_putstr_fd(str, 1);
	return (0);
}*/