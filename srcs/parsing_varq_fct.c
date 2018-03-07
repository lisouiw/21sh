#include "../twenty.h"

t_varq  *varq_simple_quote(char *s, int *i, t_varq *v)
{
    int     y;

    y = *i + 1;
    while (s[++(*i)] != 39 && s[*i])
        ;  
    v = add_struct_varq(ft_strsub(s, y, *i - y), v);
    (*i)++;
    return (v);
}

t_varq  *varq_double_quote(char *s, int *i, t_varq *v, t_env *env)
{
    int     y;

    y = *i +1;
    while (s[++(*i)] != 34 && s[*i])
        ;
    v = add_struct_varq(translate_dquote(ft_strsub(s, y, *i - y), env), v );   
    // v = add_struct_varq(ft_strsub(s, y, *i - y), v);
    (*i)++;
    return (v);
}

t_varq  *varq_env(char *s, int *i, t_varq *v, t_env *env)
{
    int     y;
    char    *sub;

    if (s || i || v )
        ;
    y = *i + 1;
    while (s[++(*i)] && s[*i] != ' ' && s[++(*i)] != '$')
        ;    
    sub = ft_strsub(s, y,  *i - y );
    v = add_struct_varq(search_var_env(sub, env), v);
    free(sub);
    if (s[*i])
        (*i)++;
    return (v);
}