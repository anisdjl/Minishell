/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:30:50 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/30 16:27:11 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

// void sig(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = &my_handler;
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	// signal(SIGINT, SIG_IGN);
// 	// signal(SIGINT, SIG_DFL);
// }

void my_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0); //en commentaire car ne marche pas sur mac mais il faut la remettre
	rl_redisplay();
}


// Mode A : Quand le Shell attend que tu tapes un truc
void    set_interactive_signals(void)
{
    struct sigaction    sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = &my_handler; // Ton handler actuel avec rl_redisplay
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);  // Ctrl-C
    sa.sa_handler = SIG_IGN;       // On ignore Ctrl-\ au prompt
    sigaction(SIGQUIT, &sa, NULL);
}

// Mode B : Quand le Shell attend qu'une commande (ex: cat) finisse
void    set_execution_signals(void)
{
    struct sigaction    sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN; // Le PARENT ignore Ctrl-C et Ctrl-
    sa.sa_flags = 0;         // pendant que l'enfant travaille
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}