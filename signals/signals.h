/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:25:59 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/28 11:56:23 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include "../minishell.h"
// #define sa_handler __sigaction_handler.sa_handler // il faut le remettre pour les ordis de l'ecole 

/* Prototype manquant sur MacOS */
//extern void rl_replace_line(const char *, int);

void	sig(void);
void	my_handler(int sig);

#endif