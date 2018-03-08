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
        return (ft_strdup(env->ctn));
    }
    free(sub);
    return (NULL);
}

char    *translate_dquote(char *s, t_env *env)
{
    int     i;
    char    *sub;
    t_varq  *v;

    i = 0;
    sub = NULL;
    v = NULL;
    while (s[i])
    {
        while (s[i] && s[i] != '$') // ["]['][$]
            ++i;
        if (s[i])
            v = varq_env(s, &i, v, env);
    }
    if (v != NULL)
        sub = change_w_varq(s, v); //coller les modif
    else
        return (s);
    return(sub);
}

void    free_varq(t_varq *v)
{
    t_varq      *tmp;
    
    while (v->next != NULL)
    {
        tmp = v;
        free(tmp->cmd);
        free(tmp);
        v = v->next;
    }
    free(v->cmd);
    free(v);
    // v = NULL;
}