#include "../../minishell.h"

int find_expand(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (ft_strchr(s, '$'))
            return 0;
        i++;
    }
    return (1);
}
void do_expand(char *s, t_env *env)
{
    int i;

    i = 1;
    
}

void expand(char **s, t_env *env)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!find_expand(s[i])){
            do_expand(s[i], env);
            printf("expand find !");
        }
        i++;
   }
}
