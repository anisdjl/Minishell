/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:35:51 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/26 17:06:57 by eprieur          ###   ########.fr       */
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
		free(line);
		printf("Syntax error : parenthese not closed\n");
		return (0);
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
		free(line);
		printf("Syntax error : quote not closed\n");
		return (0);
	}
	else
		return (1);
}

int	check_consecutive_op(t_token **token)
{
	t_token	*tmp;
	int		state;

	tmp = (*token);
	state = 1;
	while (tmp->next)
	{
		if ((tmp->type == R_PARENTHESE && tmp->next->type == L_PARENTHESE)) //()
			state = 0;
		else if ((tmp->type != WORD && tmp->type != L_PARENTHESE
				&& tmp->type != R_PARENTHESE) && ((tmp->next->type != WORD
					&& tmp->next->type != L_PARENTHESE
					&& tmp->next->type != R_PARENTHESE))) //
			state = 0;
		else if (tmp->type == WORD && tmp->next->type == L_PARENTHESE) // echo hello (echo hello)
			state = 0;
		else if (tmp->type == R_PARENTHESE && tmp->next->type == WORD) // reverse
			state = 0;
		else if (tmp->type == L_PARENTHESE && (tmp->next->type == AND || tmp->next->type == OR))
			state = 0;
		if (state == 0)
			break ;
		tmp = tmp->next;
	}
	if (state == 0)
		printf("bash: syntax error near unexpected token '%s'\n", tmp->value);
	return (state);
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
