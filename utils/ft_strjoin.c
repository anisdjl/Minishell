/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:29:37 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/12 13:20:11 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ns;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ns = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!ns)
		return (NULL);
	while (s1[i])
	{
		ns[i] = s1[i];
		i++;
	}
	while (s2[j])
		ns[i++] = s2[j++];
	ns[i] = ' ';
	ns[i + 1] = '\0';
	return (ns);
}
