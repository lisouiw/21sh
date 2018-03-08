#include "../twenty.h"

int     move_to_put_varq(char *s, int i, int o)
{
    if (o == '$')
    {
        if (s[i + 1] == '$')
        {
            while (s[++i] && s[i] == '$')
                ;
            if (s[i + 1] != ' ' || s[i + 1] != '\0')
                --i;
        }
        else
            while (s[++i] && s[i] != ' ' && s[i] != '$')
                ;
    }
    else
    {
        while (s[++i] && s[i] != o)
            ;
        ++i;
    }
    return (i);
}

char    *change_w_varq(char *s, t_varq *v)
{
    int     i;
    int     in;
    char    *nw;
    t_varq  *tmp;

    tmp = v;
    i = 0;
    nw = NULL;
    while (s[i])
    {
        in = i;
        if (s[i] && (s[i] != '$' && s[i] != 34 && s[i] != 39))
        {
            while (s[i] != '$' && s[i] != 34 && s[i] != 39)
                    ++i;
            if (i - in == 0)
            {
                nw = strjoin_free(ft_strsub(s, i, 1), nw, 2);
                ++i;
            }
            else        
                nw = strjoin_free(ft_strsub(s, in, i - in), nw, 2);
            // printf("1: %s|\n", nw);
        }
        if (s[i] && (s[i] == '$' || s[i] == 34 || s[i] == 39))
        {
            in = i;
            i = move_to_put_varq(s, i, s[i]);
            nw = strjoin_free(tmp->cmd, nw, 2);
            if (tmp->next != NULL)
                tmp = tmp->next;
            // printf("2: %s\n", nw);
        }
        // printf("-_-  %s\n", &s[i]);
    }
    return (nw);
}