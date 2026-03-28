/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:30:50 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/28 11:57:20 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sig(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &my_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	my_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0); en commentaire car ne marche pas sur mac mais il faut la remettre
	rl_redisplay();
}
