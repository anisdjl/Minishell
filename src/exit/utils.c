/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:24:26 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/26 13:27:09 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char *line) // pour fermer le programme proprement
{
	ft_free_all_malloc();
    free(line);
	rl_clear_history();
}
