#include "../twenty.h"

void    print_varq(t_varq *tmp)
{
    while (tmp->next != NULL) 
    {
        tmp = tmp->next;   
        printf("{%s}\n", tmp->cmd);
    }
    printf("{%s}\n", tmp->cmd);
    
}    

t_varq  *add_struct_varq(char *s, int y, int i, t_varq *v)
{
    t_varq  *tmp;
    t_varq  *tmp2;
    
    // printf("%i len = %i--> %s\n", y, *i - y, sub);

    if (v == NULL)
    {
        v = (t_varq*)malloc(sizeof(t_varq));
        v->cmd = ft_strsub(s, y, i - y);
        v->next = NULL;
    }
    else
    {
        tmp = v;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp2 = (t_varq*)malloc(sizeof(t_varq));
        tmp2->cmd = ft_strsub(s, y, i - y);
        printf("+++%s\n", tmp2->cmd);
        tmp2->next = NULL;
        tmp->next = tmp2;
    }
    print_varq(v);
    return (v);
}

t_varq  *varq_simple_quote(char *s, int *i, t_varq *v, t_env *env)
{
    int     y;
    // char    *sub;

    if (s || i || v || env)
        ;
    y = *i +1;
    while (s[++(*i)] != 39 && s[*i])
        ;  
    v = add_struct_varq(s, y, *i, v);
    printf("y = %i i = %i\n", y, *i);
    // printf("%i len = %i--> %s\n", y, *i - y, sub);
    (*i)++;
    return (v);
}

t_varq  *varq_double_quote(char *s, int *i, t_varq *v, t_env *env)
{
    int     y;
    char    *sub;

    if (s || i || v || env)
        ;
    y = *i +1;
    while (s[++(*i)] != 34 && s[*i])
        ;    
    sub = ft_strsub(s, y,  *i - y );
    // add_struct_varq();
    printf("%i len = %i--> %s\n", y, *i - y, sub);
    (*i)++;
    return (v);
}

t_varq  *varq_env(char *s, int *i, t_varq *v, t_env *env)
{
    int     y;
    char    *sub;

    if (s || i || v || env)
        ;
    y = *i +1;
    while (s[++(*i)] != ' ' && s[++(*i)] != '$' && s[*i])
        ;    
    sub = ft_strsub(s, y,  *i - y );
    // add_struct_varq();
    printf("%i len = %i--> %s\n", y, *i - y, sub);
    (*i)++;
    return (v);
}

t_varq  *add_varq_name(char *s, int *i, t_varq *v, t_env *env)
{
    if (s[*i] == 39)
        v = varq_simple_quote(s, &(*i), v, env);
    else if (s[*i] == 34) /// quote
        v = varq_double_quote(s, &(*i), v, env);
    else // simple variable env
        v = varq_env(s, &(*i), v, env);
    return (v);
}

t_varq  *add_varq(char *s, t_varq *v, t_env *env)
{
    int     i;

    if (env)
        ;
    i = 0;
    while (s[i])
    {
        while (s[i] && s[i] != 34 && s[i] != 39 && s[i] != '$') // ["]['][$]
            ++i;
        v = add_varq_name(s, &i, v, env);
    }
    return (v);
}

char    *quote_variable(char *s, t_varq *v, t_env *env)
{
    v = add_varq(s, NULL, env);
    return (s);
}