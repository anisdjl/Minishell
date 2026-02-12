/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:28:53 by eprieur           #+#    #+#             */
/*   Updated: 2026/02/12 13:20:11 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	safe_malloc(char **ss, int pos, int len)
{
	int	i;

	i = 0;
	ss[pos] = malloc(len * sizeof(char));
	if (!ss[pos])
	{
		while (i < pos)
		{
			free(ss[i++]);
		}
		free(ss);
		return (1);
	}
	return (0);
}

static void	strlcpy_(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i != size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static int	count_word(const char *s, char c)
{
	int	i;
	int	in_word;
	int	count;

	in_word = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (in_word == 0 && s[i] != c)
		{
			count++;
			in_word = 1;
		}
		else if (in_word == 1 && !(s[i] != c))
		{
			in_word = 0;
		}
		i++;
	}
	return (count);
}

static int	claim_word(char **ss, const char *s, char lim)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == lim && *s)
			s++;
		while (*s != lim && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (safe_malloc(ss, i, len + 1))
				return (1);
			strlcpy_(ss[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**sp;
	int		l;

	l = count_word(s, c);
	sp = malloc((l + 1) * sizeof(char *));
	if (!sp)
		return (NULL);
	sp[l] = NULL;
	if (claim_word(sp, s, c))
		return (NULL);
	return (sp);
}

// int main()
// {
//     char *s = "SalutOOOOCommentOvOaOtuOOOO?";
//     char **ns = ft_split(s, 'O');

// for (int i = 0;  ns[i]; i++)
// {
//     printf("ns : %s \n", ns[i]);
// }
// }