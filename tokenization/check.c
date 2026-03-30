/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:35:51 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/30 16:40:08 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parentheses(char *line)
{
	int	par;
	int	y;

	y = 0;
	par = 0;
	while (line[y])
	{
		if (line[y] == '(')
			par++;
		else if (line[y] == ')')
			par--;
		y++;
	}
	if (par != 0)
	{
		//free(line);
		ft_putstr_fd("Syntax error : parenthese not closed\n", 2);
		return (1);
	}
	else
		return (1);
}

int	check_quotes(char *line)
{
	int	in_squote;
	int	in_dquote;
	int	y;

	y = 0;
	in_dquote = -1;
	in_squote = -1;
	while (line[y])
	{
		if (line[y] == '\"' && in_squote == -1)
			in_dquote = -in_dquote;
		if (line[y] == '\'' && in_dquote == -1)
			in_squote = -in_squote;
		y++;
	}
	if (in_dquote == 1 || in_squote == 1)
	{
		//free(line);
		ft_putstr_fd("Syntax error : quote not closed\n", 2);
		return (1);
	}
	else
		return (1);
}

int	only_spaces(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != ' ')
			return (0);
		else
			i++;
	}
	return (1);
}

int	only_tabs(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != '\t')
			return (0);
		else
			i++;
	}
	return (1);
}

void	file_flag(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	while (tmp->next)
	{
		if ((tmp->type == HERE_DOC || tmp->type == RIGHT_A || tmp->type == LEFT_A
		|| tmp->type == APPEND) && (tmp->next->type == WORD))
			tmp->next->type = F_FILE;
		tmp = tmp->next;
	}
}
