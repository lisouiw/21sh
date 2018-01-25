#include "../twenty.h"

t_edit  *ctrl_touch(t_edit *ed, t_froz *fz, char c, t_his *hs)
{
    while (ed->rpz[2] == 0)
        ed = ed->next;
    if (c == 20 || c == 14)
        ctrl_de_test(ed, fz, c , hs);
    else if (c == 5 || c == 23)
        ed = move_word(ed, c);
    else if (c == 1 || c == 17)
        ed = up_down(ed, c);
    else if (c == 11 || c == 12)
        ed = home_end(ed, c, fz);
    // else if copier/couper/coller
    //     ;
    return (ed);
}

t_edit  *home_end(t_edit *ed, char c, t_froz *fz)
{
    int     i;

    if (c == 11) //ctrl k
    {
        ed->rpz[2] = 0;
        while (ed->rpz[0] == 0)
            ed = ed->next;
        ed->rpz[2] = giv_last(fz);    
    }
    else if (c == 12 && ed->rpz[1] == 0) //ctrl l
    {
        i = ed->rpz[2];
        ed->rpz[2] = 0;
        while (ed->rpz[1] == 0)
        {
            ed = ed->next;
            ++i;
        }
        ed->rpz[2] = i;
    }
    return(ed);
}

/// a change up and down rpz[2] to rpz[3]

t_edit  *up_down(t_edit *ed, char c)
{
    int     i;
    int     cur;
    
    cur = ed->rpz[2];
    ed->rpz[2] = 0;
    i = 0;
    if (c == 1) //ctrl a
    {
        while (ed->rpz[1] != 1 && i < g_nb->tb[0] && ++i)
            ed = ed->next;
        ed->rpz[2] = cur + i;
    }
    else if (c == 17) //ctrl q
    {
        while (ed->rpz[0] == 0 && i < g_nb->tb[0] && ++i)
            ed = ed->prev;
        ed->rpz[2] = cur - i;
    }
    return (ed);
}

t_edit  *move_word(t_edit *ed, char c)
{
    int i;

    if (c == 5 && ed->rpz[1] == 0) //ctrl e
    {
        i = ed->rpz[2];
        ed->rpz[2] = 0;
        if (ed->c[0] == '\n')
            ed = ed->next;
        while(ed->c[0] == ' ' && ed->rpz[1] == 0 && ++i)
            ed = ed->next;
        while(ed->c[0] != ' ' && ed->c[0] != '\n' && ed->rpz[1] == 0 && ++i)
            ed = ed->next;
        ed->rpz[2] = i;
    }
    else if (c == 23 && ed->rpz[0] == 0)//ctrl w
    {
        i = ed->rpz[2];
        ed->rpz[2] = 0;
        if ((ed->c[0] == ' ' || ed->c[0] == '\n') && --i)
            ed = ed->prev;
        while(ed->c[0] != ' ' && ed->c[0] != '\n' && ed->rpz[0] == 0 && --i)
            ed = ed->prev;
        if (ed->c[0] == '\n')
        {
            ed->rpz[2] = i;
            return (ed);
        }
        while(ed->c[0] == ' ' && ed->rpz[0] == 0 && --i)
            ed = ed->prev;
        if (ed->rpz[0] == 0)
            ed->next->rpz[2] = i +1;
        else
            ed->rpz[2] = i;
        
    }
    return(ed);
}

void    ctrl_de_test(t_edit *ed, t_froz *fz, char c, t_his *hs)
{
    if (c == 20) // ctrl T Lire ed avec rpz
    {
        while (ed->rpz[0] == 0)
            ed = ed->next;
        while (ed->rpz[1] == 0)
        {
            printf("%c [%i][%i][%i][%i]\n", ed->c[0], ed->rpz[0], ed->rpz[1], ed->rpz[2], ed->rpz[3]);
            ed = ed->next;
        }
        // printf("%c [%i][%i][%i][%i]\n i = %i ->%i | %i\n", ed->c[0], ed->rpz[0], ed->rpz[1], ed->rpz[2], ed->rpz[3], fz->nb[0], g_nb->tb[0], g_nb->tb[1]);
        
        printf("%c [%i][%i][%i][%i]\n i = %i ->%i | %i\n sfz->cmd = {%s} && mode[3] == %i\n", ed->c[0], ed->rpz[0], ed->rpz[1], ed->rpz[2], ed->rpz[3], fz->nb[0], g_nb->tb[0], g_nb->tb[1], fz->cmd, fz->mode[3]);
    }
    else if (c == 14) // ctrl n
    {
        if (!hs)
            return;
        while (hs && hs->next != NULL)
        {
            printf("->%s\n", hs->cmd);
            hs = hs->next;
        }
        printf("->%s\n", hs->cmd);
            
    }
    sleep(3);
}