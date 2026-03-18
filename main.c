/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:57:30 by adjelili          #+#    #+#             */
/*   Updated: 2026/03/16 17:52:14 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ======= TEST ======= */
t_tree *tmp_tree(void)
{
    t_tree *tree;

    tree = malloc(sizeof(t_tree));
    if (!tree) return (NULL);
    tree->type = WORD;
    tree->n_value = NULL;
    ft_lstadd_back_value(&tree->n_value, ft_lstnew_value("\"$USER$:$HOME$\""));
    tree->redirs = NULL;
    tree->left = NULL;
    tree->right = NULL;

    return (tree);
}
/*====================*/

int main(int argc, char **argv, char **envp)
{
    char *line;
    int fd;
    t_lexer		*lexer;
	t_env		*env;

	env = get_env(envp);
    domain_expand(tmp_tree(), env); // domain_expand(le noeud de l'ast a etendre, l'environnement);
    while (1)
    {
        line = readline("minishell> ");
        if (!line || line[0] == '\n' || line[0] == '\0' || only_spaces(line))
        {   
			free(line); 
			continue;
		}
        history(line);
        if (!check_parentheses(line) || !check_quotes(line))
            continue;
        lexer = ft_lexer(line);
		exec(AST_launcher(lexer->content), env);
		// printf("%d\n", env->exit_status->exit_status);
        ft_free_all_malloc();
		//free env
        free(line);
    }
    return (0);
}
