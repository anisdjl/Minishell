/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/18 13:37:00 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token(char *line)
{
	t_lexer	*lexer;

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
	// besoin de count word ? pas sur vue que c'est en liste chainee
	fill_tokens(line, &data);
}

void	fill_tokens(char *line, t_lexer **lexer)
{
	int	y;
	
	y = 0;
	
}
// int	count_elem(char *line)
// {
// 	int y;
// 	int nb_elem;

// 	nb_elem = 0;
// 	y = 0;
// 	while (line[y])
// 	{
// 		if (ft_isalpha[y])
			
// 	}
// }
