/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_and_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:36:56 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/23 15:22:02 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	operator(char c)
{
	if (c == '>' || c == '<'
		|| c == '|'
		|| c == '&' || c == '(' || c == ')')
		return (1);
	else
		return (0);
}

void	operator_token(t_lexer *lexer, char *line, int *y)
{
	if (operator(line[*y]) && line[*y + 1] != line[*y])
	{
		create_token(lexer);
		add_to_buffer(lexer, line[*y]);
		create_token(lexer);
	}
	else if (operator(line[*y]) && line[*y + 1] == line[*y])
	{
		create_token(lexer);
		add_to_buffer(lexer, line[*y]);
		add_to_buffer(lexer, line[*y + 1]);
		create_token(lexer);
		(*y)++;
	}
	else
		return ;
}

t_enum	return_type(t_token *tmp)
{
	if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '|')
		return (PIPE);
	else if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, "||", 2) == 0)
		return (OR);
	else if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, "&&", 2) == 0)
		return (AND);
	else if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strlen(tmp->value) == 2 && ft_strncmp(tmp->value, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '>')
		return (RIGHT_A);
	else if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '>')
		return (LEFT_A);
	else if (ft_strlen(tmp->value) == 1 && tmp->value[0] == '(')
		return (L_PARENTHESE);
	else if (ft_strlen(tmp->value) == 1 && tmp->value[0] == ')')
		return (R_PARENTHESE);
	else
		return (WORD);
}

void	put_types(t_lexer *lexer)
{
	t_token	*tmp;

	tmp = lexer->content;
	while (tmp)
	{
		tmp->type = return_type(tmp);
		tmp = tmp->next;
	}
	tmp = lexer->content;
	while (tmp)
	{
		if (need_expand(tmp))
			tmp->flag |= F_EXPAND;
		tmp = tmp->next;
	}
}

int	need_expand(t_token *tmp)
{
	int	y;

	if (tmp->flag & F_SQUOTE)
		return (0);
	y = 0;
	while (tmp->value[y])
	{
		if (tmp->value[y] == '$' && tmp->value[y + 1]
			&& tmp->value[y + 1] != ' ')
			return (1);
		else if (tmp->value[y] == '*' && !(tmp->flag & F_DQUOTE))
			return (1);
		y++;
	}
	return (0);
}
