#include "../twenty.h"

t_edit  *paste(t_edit *ed)
{
    return (ed);
}

t_edit  *copy(t_edit *ed, t_froz **fz)
{
    if ((*fz)->mode[0] == 1) // give the cmd
        (*fz)->paste = keep_paste(&ed, NULL);
    (*fz)->mode[0] = ((*fz)->mode[0] == 0) ? 1 : 0;
    if ((*fz)->mode[1] == 1 || (*fz)->mode[0] == 0)
    {
        while (ed->rpz[0] == 0)
            ed = ed->next;
        while (ed->rpz[1] == 0)
        {
            ed->rpz[4] = 0;
            ed = ed->next;
        }
        ed->rpz[4] = 0;
        while (ed->rpz[2] == 0)
            ed = ed->next;
    }
    else
        ed->rpz[4] = 1;
    return (ed);
}

void    free_cut(t_edit **ed)
{
    t_edit  *tmp;

    while ((*ed)->rpz[0] == 0)
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 0)
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 1)
    {
        tmp = *ed;
        (*ed)->prev->next = (*ed)->next;
        (*ed)->next->prev = (*ed)->prev;
        free(tmp);
        *ed = (*ed)->next;
    }
    (*ed)->rpz[2] = (*ed)->rpz[3];
    
    while ((*ed)->rpz[0] == 0)
        *ed = (*ed)->next;
    while (((*ed)->rpz[1] == 0 && (*ed)->rpz[3] < (*ed)->next->rpz[3]))
    {
        while ((*ed)->rpz[1] == 0)
        {
            (*ed) = (*ed)->next;
            if ((*ed)->prev->c[0] == '\n' && tmp->prev->rpz[3] % g_nb->tb[0] != 0)
                (*ed)->rpz[3] = ((((*ed)->prev->rpz[3] / g_nb->tb[0]) + 1 ) * g_nb->tb[0]) + 1;
            else
                (*ed)->rpz[3] = (*ed)->prev->rpz[3] + 1;
        }
        if ((*ed)->prev->c[0] == '\n' && (*ed)->prev->rpz[3] % g_nb->tb[0] != 0)
            (*ed)->rpz[3] = ((((*ed)->prev->rpz[3] / g_nb->tb[0]) + 1 ) * g_nb->tb[0]) + 1;
    }

    
    ctrl_de_test(*ed, NULL, 20, NULL);
}

void  cut(t_edit **ed, t_froz **fz)
{
    if ((*fz)->mode[1] == 1) // give the cmd
    {
        (*fz)->paste = keep_paste(&(*ed), NULL);
        free_cut(&(*ed));
    }
    (*fz)->mode[1] = ((*fz)->mode[1] == 0) ? 1 : 0;
    if ((*fz)->mode[0] == 1 || (*fz)->mode[1] == 0)
    {
        while ((*ed)->rpz[0] == 0)
            *ed = (*ed)->next;
        while ((*ed)->rpz[1] == 0)
        {
            (*ed)->rpz[4] = 0;
            *ed = (*ed)->next;
        }
        (*ed)->rpz[4] = 0;
        while ((*ed)->rpz[2] == 0)
            *ed = (*ed)->next;
    }
    else
        (*ed)->rpz[4] = 1;
}


char    *keep_paste(t_edit **ed, char *s)
{
    int     i;
    int     a;

    a = -1;
    i = 0;
    while ((*ed)->rpz[0] == 0) // revenir debut de la liste
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 0) // init cut/copy
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 1 && (*ed)->rpz[1] == 0) // count cut/copy
    {
        ++i;
        *ed = (*ed)->next;
    }
    while ((*ed)->rpz[0] == 0) // revenir debut de la liste
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 0) // init cut/copy
        *ed = (*ed)->next;
    if (!(s = (char*)malloc((i + 1)* sizeof(char))))
        return (NULL);
    while (++a < i)
    {
        s[a] = (*ed)->c[0];
        *ed = (*ed)->next;
    }
    s[a] = '\0';
    return (s);
}