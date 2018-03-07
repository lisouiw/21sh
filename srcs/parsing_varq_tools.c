#include "../twenty.h"

void    print_varq(t_varq *tmp)
{
    if (tmp)
    {
        while (tmp->next != NULL) 
        {
            printf("{%s}\n", tmp->cmd);
            tmp = tmp->next;   
        }
        printf("{%s}\n", tmp->cmd);
    }
}    

char    *search_var_env(char *sub, t_env env)
{
    char    *tmp;
    tmp = ft_strsub(env.name, 0, ft_strlen(env.name) - 1);
    while (ft_strcmp(sub, tmp) != 0)
    {
        if (env.next != NULL)
            env = *env.next;
        else
            break;
        free(tmp);
        tmp = ft_strsub(env.name, 0, ft_strlen(env.name) - 1);
    }
    if (ft_strcmp(sub, tmp) == 0)
        return (env.ctn);
    return (NULL);
}