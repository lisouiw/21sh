#include "../twenty.h"

void    add_here_struct(t_froz *fz, char *s)
{
    char    **t;
    t = ft_strsplit(s, ' ');
    if ((!fz->here->delim) && fz->here->prev == NULL &&  fz->here->next == NULL )
    {
        // printf("INIT %s\n", s);
        //add struct actuel
        fz->here->delim = ft_strdup(t[1]);
        fz->here->doc = NULL;
        fz->here->ok[0] = 0;
        fz->here->prev = NULL;
        //init here->next
        fz->here->next = (t_here*)malloc(sizeof(t_here));
        fz->here->next->prev = fz->here;
        fz->here = fz->here->next;
        fz->here->delim = NULL;
        fz->here->next = NULL;
    }
    else if (fz->here->delim == NULL)
    {
        // printf("HERE %s\n", s);
        fz->here->delim = ft_strdup(t[1]);
        fz->here->doc = NULL;
        fz->here->ok[0] = 0;
        //init here->next
        fz->here->next = (t_here*)malloc(sizeof(t_here));
        fz->here->next->prev = fz->here;
        fz->here = fz->here->next;
        fz->here->delim = NULL;
        fz->here->next = NULL;
    }
    else
        fz->here = fz->here->next;
    free_tab(t);
}

int     check_struct(t_froz *fz)
{
    while(fz->here->prev != NULL)
        fz->here = fz->here->prev;
    while(fz->here->prev != NULL)
        fz->here = fz->here->prev;
    return (1);
}

int    add_here(t_froz *fz, t_cmd *ex)
{
    print_ex_up(ex);
    fz->mode[3] = 6;
    while (ex->prev->prev != NULL)
        ex = ex->prev;
    while (ex->cmd != NULL)
    {
        // printf("->%s\n", fz->here->delim);
        if (ex->type == 6)
            add_here_struct(fz, ex->cmd);
        ex = ex->next;
    }
    print_here(fz);
    // check_struct(fz);
    return (0);
}