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

char    *search_var_env(char *sub, t_env *env)
{
    char    *tmp;

    tmp = ft_strsub(env->name, 0, ft_strlen(env->name) - 1);
    while (ft_strcmp(sub, tmp) != 0)
    {
        if (env->next != NULL)
            env = env->next;
        else
            break;
        free(tmp);
        tmp = ft_strsub(env->name, 0, ft_strlen(env->name) - 1);
    }
    free(tmp);
    if (ft_strcmp(sub, tmp) == 0)
    {
        free(sub);
        return (env->ctn);
    }
    free(sub);
    return (NULL);
}

char    *translate_dquote(char *s, t_env *env)
{
    int     i;
    int     in;
    char    *sub;

    i = 0;
    sub = NULL;
    while (s[i])
    {
        in = i;
        if (s[i] && s[i] != '$')
        {
            while (s[i] && s[i] != '$')
                    ++i;
            sub = strjoin_free(ft_strsub(s, in, i - in), sub, 2);
        }
        if (s[i] && s[i] == '$')
        {
            in = i;
            while (s[++i] && s[i] != ' ' && s[i] != '$')
                ;
            sub = strjoin_free(search_var_env(ft_strsub(s, in + 1, i - in - 1), env), sub, 3);
        }
    }
    return(sub);
}

void    free_varq(t_varq *v)
{
    t_varq      *tmp;
    if (!v)
        return;
    while (v->next != NULL)
    {
        tmp = v;
        free(tmp->cmd);
        free(tmp);
        v = v->next;
    }
    free(v->cmd);
    free(v);
}