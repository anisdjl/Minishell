/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:31:26 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 17:00:27 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# define _APPLE_C_SOURCE
# define _DARWIN_C_SOURCE
# include "header/bulltin.h"
# include "header/env.h"
# include "header/exec.h"
# include "header/expand.h"
# include "header/gc.h"
# include "header/parsing.h"
# include "header/pipe.h"
# include "header/redir.h"
# include "header/signals.h"
# include "libft/libft.h"
# include "sys/types.h"
# include "sys/wait.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

void							history(char *line);
void							*ft_malloc(size_t nmemb, size_t size);
void							ft_free_malloc(void *ptr);
void							ft_free_all_malloc(void);

#endif