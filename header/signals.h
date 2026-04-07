/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:25:59 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 16:22:03 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	set_interactive_signals(void);
void	set_execution_signals(void);
void	my_handler(int sig);
void	handler_heredoc(int sig);

#endif