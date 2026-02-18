/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/18 10:42:43 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token(char *line)
{
	t_data	*data;

	int nb_elem;
	y = 0;
	if (!line)
		return ;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		free(line); // mettre une ft pour tout free
		return ;
	}
	nb_elem = count_elem(line);
}

int	count_elem(char *line)
{
	int y;
	int nb_elem;

	nb_elem = 0;
	y = 0;
	while (line[y])
	{
		if (ft_isalpha)
	}
}
