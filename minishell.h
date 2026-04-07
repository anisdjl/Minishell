/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:31:26 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/07 14:34:34 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef LLONG_MAX
#  define LLONG_MAX 9223372036854775807LL
# endif
# ifndef LLONG_MIN
#  define LLONG_MIN (-9223372036854775807LL - 1LL)
# endif

# define _XOPEN_SOURCE 700
# define _APPLE_C_SOURCE
# define _DARWIN_C_SOURCE
# include <sys/ioctl.h>
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/stat.h>
# include "header/parsing.h"
# include "header/expand.h"
# include "libft/libft.h"
# include "garbage_collector/gc.h"
# include "env/env.h"
# include "sys/wait.h"
# include "sys/types.h"
# include "exec/exec.h"
# include "libft/libft.h"
# include <signal.h>
# include "signals/signals.h"
# include "header/expand.h"

extern volatile sig_atomic_t	g_signal;

void	history(char *line);
void	*ft_malloc(size_t nmemb, size_t size);
void	ft_free_malloc(void *ptr);
void	ft_free_all_malloc(void);

#endif