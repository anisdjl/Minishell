#include "../../minishell.h"

t_value_node *ft_lstnew_value(char *content)
{
	t_value_node *lst;

	lst = malloc(sizeof(t_value_node));
	if (lst == 0)
		return (0);
	lst->value = content;
	lst->next = 0;
	return (lst);
}

void	ft_lstadd_back_value(t_value_node **lst, t_value_node *new)
{
	t_value_node	*cursor;

	cursor = *lst;
	if (cursor)
	{
		while (cursor->next != NULL)
		{
			cursor = cursor->next;
		}
		cursor->next = new;
	}
	else if (!cursor)
		*lst = new;
}
