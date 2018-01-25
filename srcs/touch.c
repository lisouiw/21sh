#include "../twenty.h"

t_edit  *touch(t_edit *ed, t_froz **fz, t_his **hs)
{
    if ((*fz)->buf[1] == 0 && (*fz)->buf[2] == 0)
    {
        if ((*fz)->buf[0] > 0 && (*fz)->buf[0] < 27)
            ed = ctrl_touch(ed, *fz, (*fz)->buf[0], *hs);
        else if ((*fz)->buf[0] == 127)
        {
            while (ed->rpz[2] == 0)
                ed = ed->next;
            if (ed->rpz[0] != 0)
                return(ed);
            ed = erase_ed(ed);
            (*fz)->nb[0] = (*fz)->nb[0] - 1;
            if (ed->rpz[0] == 1 && ed->rpz[1] == 1 && ed->rpz[2] == 3) // tout erase donc hsto on
                (*fz)->mode[2] = 1;
        }
        else
        {
            ed = add_ed(ed, (*fz)->buf[0], NULL);
            (*fz)->nb[0] = (*fz)->nb[0] + 1;
            (*fz)->mode[2] = 0;
        }
    }
    else
        ed = extern_touch(ed, &(*fz), &(*hs));
    print_shell(ed, *fz);
    return (ed);
}


t_edit  *extern_touch(t_edit *ed, t_froz **fz, t_his **hs)
{
    while (ed->rpz[2] == 0) //se mettre au nv cursor
        ed = ed->next;
    if ((*fz)->buf[0] == 27 && (*fz)->buf[1] == 91 && ((*fz)->buf[2] == 68 || (*fz)->buf[2] == 67))  // left/right
        ed = left_right(ed, *fz);
    else if (*hs && (*fz)->mode[2] > 0 && (*fz)->buf[0] == 27 && (*fz)->buf[1] == 91 && ((*fz)->buf[2] == 65 || (*fz)->buf[2] == 66)) //historique : haut/bas
    { 
        *hs = histo(*hs, (*fz)->buf[2], &ed, &(*fz));
    }
    return (ed);
}

t_his   *histo(t_his *hs, char c, t_edit **ed, t_froz **fz)
{
    int     i;

    i = -1;
    free_ed(&(*ed), *fz);   
    if (c == 65 && hs->next != NULL)  //historique : haut
    {
        hs = hs->next;
        if (hs->cmd == NULL)
        {
            (*fz)->nb[0] = giv_last(*fz);
            return(hs);
        }
        while (hs->cmd[++i])
            *ed = add_ed(*ed, hs->cmd[i], NULL);
        *ed = giv_position(*ed, giv_last(*fz));
        (*fz)->nb[0] = i + giv_last(*fz);
    }
    else if (c == 66 && hs->prev != NULL) //historique : bas
    {
        hs = hs->prev;
        if (hs->cmd == NULL)
        {
            (*fz)->nb[0] = giv_last(*fz);
            return(hs);
        }
        while (hs->cmd[++i])
            *ed = add_ed(*ed, hs->cmd[i], NULL);
        *ed = giv_position(*ed, giv_last(*fz));
        (*fz)->nb[0] = i + giv_last(*fz);
    }
    return (hs);
}

t_edit  *giv_position(t_edit *ed, int i)
{
    while (ed->rpz[0] == 0)
        ed = ed->next;
    while (ed->rpz[1] == 0)
    {
        if (ed->prev->c[0] == '\n' && i % g_nb->tb[0] != 0)
        {
            i = (((i / g_nb->tb[0]) +1 ) * g_nb->tb[0]) + 1;
            ed->rpz[3] = i;
        }
        else
            ed->rpz[3] = i;
        ++i;
        ed = ed->next;
    }
    if (ed->prev->c[0] == '\n' && i % g_nb->tb[0] != 0)
    {
        i = (((i / g_nb->tb[0]) +1 ) * g_nb->tb[0]) + 1;
        ed->rpz[3] = i;
    }
    else
        ed->rpz[3] = i;
    return (ed);
}


t_edit  *left_right(t_edit *ed, t_froz *fz)
{
    if (fz->buf[2] == 68 && ed->rpz[0] == 0)  // left
    {
        ed->prev->rpz[2] = ed->rpz[2] - 1;
        ed->rpz[2] = 0;
    }
    else if (fz->buf[2] == 67 && ed->next->rpz[0] == 0) //right
    {
        ed->next->rpz[2] = ed->rpz[2] + 1;   
        ed->rpz[2] = 0;
    }
    return(ed);
}