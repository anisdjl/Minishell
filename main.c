/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/02/26 17:13:06 by adjelili         ###   ########.fr       */
=======
/*   Updated: 2026/02/26 16:35:09 by eprieur          ###   ########.fr       */
>>>>>>> a1429d981532d43689c85e198499901c7f6c7344
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *line;
    int fd;
    t_lexer    *lexer;

    fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        return (0);
    while (1)
    {
        line = readline("minishell> ");
        if (!line || line[0] == '\n' || line[0] == '\0' || only_spaces(line))
            continue;
        if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) == 4)
            return (0);
        history(line);
        if (!check_parentheses(line) || !check_quotes(line))
            continue;
        lexer = ft_lexer(line);
        debug_tokens(&lexer->content);
		AST_launcher(lexer->content);
        ft_free_all_malloc();
        free(line);
    }
    return (0);
}
