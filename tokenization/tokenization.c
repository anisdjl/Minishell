/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:35:14 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/17 17:11:08 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_node(t_lexer *head, char *value, int type, int priority)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
	{
		//ft_free_list
		exit(EXIT_FAILURE);
	}
	head->next = node;
	node->value = value;
	node->type = type;
	node->priority = priority;
	node->next = NULL;
}

void	tokeniasation(char *line)
{
	int	y;
	int i;
	char	*value;
	int	a;
	t_lexer	*head;

	i = 0;
	y = 0;
	head = malloc(sizeof(t_lexer));
	while (line[y])
	{
		a = 0;
		while (line[y] != '|')
			y++;
		value = malloc(sizeof(char) * (y - i) + 2);
		if (!value)
			exit(EXIT_FAILURE);
		while (line[i] != '|')
		{	
			value[a] = line[i];
			a++;
			i++;
		}
		create_node
	}
}
