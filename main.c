/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/11 12:38:14 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *line;
    int fd;
    t_lexer		*lexer;
	t_env		*env;

	env = get_env(envp);
    while (1)
    {
        line = readline("minishell> ");
        if (!line || line[0] == '\n' || line[0] == '\0' || only_spaces(line))
            continue;
        // if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) == 4)
        //     return (0);
        history(line);
        if (!check_parentheses(line) || !check_quotes(line))
            continue;
        lexer = ft_lexer(line);
		exec(AST_launcher(lexer->content), env);
		printf("%d\n", env->exit_status->exit_status);
        ft_free_all_malloc();
		//free env
        free(line);
    }
    return (0);
}
