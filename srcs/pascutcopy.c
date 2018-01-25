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

t_edit  *cut(t_edit *ed, t_froz **fz)
{
    if ((*fz)->mode[1] == 1) // give the cmd
        (*fz)->paste = keep_paste(&ed, NULL);
    (*fz)->mode[1] = ((*fz)->mode[1] == 0) ? 1 : 0;
    if ((*fz)->mode[0] == 1 || (*fz)->mode[1] == 0)
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

char    *keep_paste(t_edit **ed, char *s)
{
    int     i;
    int     a;

    a = -1;
    i = 0;
    while ((*ed)->rpz[0] == 0)
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 0)
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 1 && (*ed)->rpz[1] == 0)
    {
        ++i;
        *ed = (*ed)->next;
    }
    while ((*ed)->rpz[0] == 0)
        *ed = (*ed)->next;
    while ((*ed)->rpz[4] == 0)
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