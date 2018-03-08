#include "../twenty.h"

t_varq  *add_struct_varq(char *s, t_varq *v)
{
    t_varq  *tmp;
    t_varq  *tmp2;
    
    if (v == NULL)
    {
        v = (t_varq*)malloc(sizeof(t_varq));
        v->cmd = s;
        v->next = NULL;
    }
    else
    {
        tmp = v;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp2 = (t_varq*)malloc(sizeof(t_varq));
        tmp2->cmd = s;
        tmp2->next = NULL;
        tmp->next = tmp2;
    }
    return (v);
}



t_varq  *add_varq(char *s, int *i, t_varq *v, t_env *env)
{
    // printf("==ENTREE==%s\n", &s[*i]);
    if (s[*i] == 39) //quote
        v = varq_simple_quote(s, &(*i), v);
    else if (s[*i] == 34) /// dquote
        v = varq_double_quote(s, &(*i), v, env);
    else  // simple variable env
        v = varq_env(s, &(*i), v, env);
    return (v);
}

t_varq  *add_varq_loop(char *s, t_varq *v, t_env *env)
{
    int     i;

    if (env)
        ;
    i = 0;
    while (s[i])
    {
        while (s[i] && s[i] != 34 && s[i] != 39 && s[i] != '$') // ["]['][$]
            ++i;
        if (s[i])
            v = add_varq(s, &i, v, env); //i pour bouger
    }
    return (v);
}

char    *quote_variable(char *s, t_varq *v, t_env *env)
{
    char    *nw;

    nw = NULL;
    v = add_varq_loop(s, NULL, env); //add les modif
    // print_varq(v);
    if (v != NULL)
        nw = change_w_varq(s, v); //coller les modif
    else
        return(s);
    // printf("nw = %s\n", nw);
    free_varq(v);
    return (nw);
}