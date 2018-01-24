#include "../twenty.h"

void    free_ed(t_edit **ed, t_froz *fz)
{
    if ((*ed)->rpz[0] == 1 && (*ed)->rpz[1] == 1)
        return;
    while ((*ed)->rpz[0] == 0)
        *ed = (*ed)->next;
    while ((*ed)->rpz[1] == 0)
    {
        *ed = (*ed)->next;
        free((*ed)->prev);
    }
    (*ed)->rpz[0] = 1;
    (*ed)->rpz[2] = giv_last(fz);
    (*ed)->rpz[3] = giv_last(fz);
    (*ed)->prev = *ed;
    (*ed)->next = *ed;
}

void    modif_edit(t_edit **ed, t_edit **nw)
{
    t_edit *tmp;

    tmp = *ed;
    if ((*ed)->rpz[0] == 1)
    {
        (*ed)->rpz[0] = 0;
        (*nw)->rpz[0] = 1;
    }
    (*nw)->rpz[3] = (*ed)->rpz[3];
    (*ed)->rpz[3] = (*nw)->rpz[3] + 1;
    (*ed)->rpz[2] = (*ed)->rpz[2] + 1;
    if (tmp->rpz[1] == 0 && tmp->rpz[3] >= tmp->next->rpz[3])
    {
        // printf("%i, %i\n", tmp->rpz[3], tmp->next->rpz[3]);
        while (tmp->rpz[1] == 0)
        {
            tmp->next->rpz[3] = tmp->rpz[3] + 1;
            tmp = tmp->next;
        }
        // sleep(1);
    }
}

t_edit  *add_ed(t_edit *ed, char c, t_edit *nw)
{
    if (!(nw = (t_edit*)malloc(sizeof(t_edit))))
        return(ed);
    while (ed->rpz[2] == 0)
        ed = ed->next;
    nw->c[0] = c;
    nw->rpz[0] = 0;
    nw->rpz[1] = 0;
    nw->rpz[2] = 0;
    modif_edit(&ed, &nw);
    if (ed->rpz[0] == 1 && ed->rpz[1] == 1)
    {
        nw->next = ed;
        nw->prev = ed;
        ed->next = nw;
        ed->prev = nw;
    }
    else
    {
        nw->next = ed;
        nw->prev = ed->prev;
        ed->prev->next = nw;
        ed->prev = nw;
    }
    
    return(nw);
}

t_edit  *init_edit(t_edit *init)
{
    if (!(init = (t_edit*)malloc(sizeof(t_edit))))
        return(NULL);
    init->c[0] = '\0';
    init->next = init;
    init->prev = init;
    init->rpz[0] = 1;
    init->rpz[1] = 1;
    init->rpz[2] = 3;
    init->rpz[3] = 3;
    init->rpz[4] = 0; 
    return(init);
}

t_edit  *erase_ed(t_edit *ed)
{
    t_edit  *erase;

    while(ed->rpz[2] == 0)
        ed = ed->next;
    if (ed->rpz[0] == 1)
        return (ed);
    ed->rpz[2] = ed->rpz[2] - 1;
    ed->rpz[3] = ed->rpz[3] - 1;     
    erase = ed->prev;
    if (ed->prev->rpz[0] == 1)
        ed->rpz[0] = 1;
    ed->prev = ed->prev->prev;
    ed->prev->next = ed;
    while (ed->rpz[1] == 0)
    {
        ed = ed->next;
        ed->rpz[3] = ed->rpz[3] - 1;     
    
    }
    free(erase);
    return(ed);
}
