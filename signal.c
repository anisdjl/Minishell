/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:06:19 by anis              #+#    #+#             */
/*   Updated: 2026/03/03 16:20:00 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _APPLE_C_SOURCE
#define _DARWIN_C_SOURCE
# include <signal.h>
#include <unistd.h>
#include <stdio.h>
# include "sys/wait.h"
int main(void)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			printf("hello world\n");
			usleep(20000);
		}
	}
	else
	{
		kill(pid, SIGSTOP);
		sleep(1);
		kill(pid, SIGCONT);
		sleep(1);
		kill(pid, SIGKILL);
		wait (NULL);
	}
}

// pour reafficher le prompt on utilise des rl_on_new_line, rl_replace line, rl_redisplay