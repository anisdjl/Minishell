/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:25:59 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/14 16:01:13 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H\

#include "../minishell.h"
#define sa_handler __sigaction_handler.sa_handler

void	sig(void);
void	my_handler(int sig);

#endif