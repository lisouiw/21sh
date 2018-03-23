#include "../twenty.h"

void    add_here_struct(t_froz *fz, char *s)
{
    char    **t;

    t = ft_strsplit(s, ' ');
    if ((!fz->here->delim) && fz->here->prev == NULL &&  fz->here->next == NULL )
    {
        printf("INIT %s\n", s);
        fz->here->delim = ft_strdup(t[1]);
        fz->here->doc = NULL;
        fz->here->ok[0] = 0;
        fz->here->ok[1] = 0;
        fz->here->next = NULL;
        fz->here->prev = NULL;
    }
    else if (fz->here->next != NULL || fz->here->ok[1] == 0)
        fz->here = fz->here->next;
    else
    {
        printf("NON INIT %s\n", s);
        fz->here->next = (t_here*)malloc(sizeof(t_here));
        fz->here->next->prev = fz->here;
        fz->here = fz->here->next;
        fz->here->next = NULL;
        fz->here->delim = ft_strdup(t[1]);
        fz->here->doc = NULL;
        fz->here->ok[0] = 0;
        fz->here->ok[1] = 0;
    }
    free_tab(t);
}

void    add_here(t_froz *fz, t_cmd *ex)
{
    while (ex->prev->prev != NULL)
        ex = ex->prev;
    while (ex->cmd != NULL)
    {
        printf("->%s\n", ex->cmd);
        if (ex->type == 6)
            add_here_struct(fz, ex->cmd);
        ex = ex->next;
    }
    print_here(fz);
    while(fz->here->prev != NULL)
        fz->here = fz->here->prev;
}