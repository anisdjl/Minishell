/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:40:37 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/06 11:26:47 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char ***tab, int x)
{
	while (x >= 0)
	{
		free ((*tab)[x]);
		x--;
	}
	free (*tab);
	return (NULL);
}

static int	ft_nbwords(char const *s, char c)
{
	int	nbwords;
	int	a;

	a = 0;
	nbwords = 0;
	while (s[a])
	{
		if (s[a] != c
			&& (s[a + 1] == c || s[a + 1] == '\0'))
		{
			nbwords++;
			a++;
		}
		else
			a++;
	}
	return (nbwords);
}

static void	ft_length(char const *s, char c, int *i, int *j)
{
	while (s[*i] == c)
		(*i)++;
	*j = *i;
	while (s[*j] != c && s[*j] != '\0')
		(*j)++;
}

static char	*ft_fill(const char *s, char *tab, int i, int j)
{
	int	k;

	k = 0;
	while (i < j)
	{
		tab[k] = s[i];
		k++;
		i++;
	}
	tab[k] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		m;
	int		nbwords;

	i = 0;
	j = 0;
	m = 0;
	nbwords = ft_nbwords(s, c);
	tab = ft_malloc(1, sizeof(char *) * (nbwords + 1));
	if (!tab)
		return (NULL);
	while (m < nbwords)
	{
		ft_length(s, c, &i, &j);
		tab[m] = ft_malloc(1, sizeof(char) * (j - i) + 1);
		if (!tab[m])
			return (ft_free(&tab, m));
		ft_fill(s, tab[m], i, j);
		i = j;
		m++;
	}
	tab[m] = NULL;
	return (tab);
}

/*#include <stdio.h>

int	main(void)
{
	char str[] = "hello hru today !";
	int l;
	char **tab2 = ft_split(str, ' ');

	l = 0;
	while (l < 3)
	{
		printf("%s\n", tab2[l]);
		l++;
	}
	free (tab2);
	return (0);
}*/
