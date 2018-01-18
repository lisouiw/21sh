#include "../twenty.h"

t_edit  *touch(t_edit *ed, t_froz *fz)
{
    if (fz->buf[1] == 0 && fz->buf[2] == 0)
    {
        if (fz->buf[0] > 0 && fz->buf[0] < 27)
            ed = ctrl_touch(ed, fz, fz->buf[0]);
        else if (fz->buf[0] == 127)
        {
            ed = erase_ed(ed);
            fz->nb[0] = fz->nb[0] - 1;
        }
        else
        {
            ed = add_ed(ed, fz->buf[0], NULL);
            fz->nb[0] = fz->nb[0] + 1;
        }
    }
    else
        ed = extern_touch(ed, fz);
    print_shell(ed, fz);
    return (ed);
}

t_edit  *ctrl_touch(t_edit *ed, t_froz *fz, char c)
{
    if (fz->buf[0])
        ;
    if (c == 20) // ctrl T Lire ed avec rpz
    {
        while (ed->rpz[0] == 0)
            ed = ed->next;
        while (ed->rpz[1] == 0)
        {
            printf("%c [%i][%i][%i]\n", ed->c[0], ed->rpz[0], ed->rpz[1], ed->rpz[2]);
            ed = ed->next;
        }
        printf("%c [%i][%i][%i]\n i = %i ->%i | %i\n\n", ed->c[0], ed->rpz[0], ed->rpz[1], ed->rpz[2], fz->nb[0], g_nb->tb[0], g_nb->tb[1]);
    }
    sleep(3);
    return (ed);
}

t_edit  *extern_touch(t_edit *ed, t_froz *fz)
{
    while (ed->rpz[2] == 0) //se mettre au nv cursor
        ed = ed->next;
    if (fz->buf[0] == 27 && fz->buf[1] == 91 && fz->buf[2] == 68 && ed->rpz[0] == 0)  // left
    {
        ed->prev->rpz[2] = ed->rpz[2] - 1;
        ed->rpz[2] = 0;
    }
    else if (fz->buf[0] == 27 && fz->buf[1] == 91 && fz->buf[2] == 67 && ed->next->rpz[0] == 0) //right
    {
        ed->next->rpz[2] = ed->rpz[2] + 1;   
        ed->rpz[2] = 0;
    }
    return (ed);
}