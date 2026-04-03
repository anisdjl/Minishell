/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:25:59 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/03 15:53:04 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include "../minishell.h"
// #define sa_handler __sigaction_handler.sa_handler // il faut le remettre pour les ordis de l'ecole 

/* Prototype manquant sur MacOS */
//extern void rl_replace_line(const char *, int);

// void	sig(void);
void    set_interactive_signals(void);
void    set_execution_signals(void);
void	my_handler(int sig);
void	handler_heredoc(int sig);

#endif