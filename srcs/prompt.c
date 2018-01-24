#include "../twenty.h"

void    put_prompt_init(t_froz **fz)
{
    // put_prompt(*fz);
    if ((*fz)->mode[3] == 0)
    {
        ft_putstr("\033[0;33;40m>>\033[0m");
        (*fz)->nb[0] = 3;
    }
    else if ((*fz)->mode[3] == 1)
    {
        ft_putstr("\033[0;33;40mquote>\033[0m");
        (*fz)->nb[0] = 7;
    }
    else if ((*fz)->mode[3] == 2)
    {
        ft_putstr("\033[0;33;40mdquote>\033[0m");
        (*fz)->nb[0] = 8;
    }
    else if ((*fz)->mode[3] == 3)
    {
        ft_putstr("\033[0;33;40mpipe>\033[0m");
        (*fz)->nb[0] = 6;
    }
    else if ((*fz)->mode[3] == 4)
    {
        ft_putstr("\033[0;33;40mcmdand>\033[0m");
        (*fz)->nb[0] = 8;
    }
    else if ((*fz)->mode[3] == 5)
    {
        ft_putstr("\033[0;33;40mcmdor>\033[0m");
        (*fz)->nb[0] = 7;
    }
    else if ((*fz)->mode[3] == 6)
    {
        ft_putstr("\033[0;33;40mheredoc>\033[0m");
        (*fz)->nb[0] = 9;
    }
}

void    put_prompt(t_froz *fz)
{    
    if (fz->mode[3] == 0)
        ft_putstr("\033[0;33;40m>>\033[0m");
    else if (fz->mode[3] == 1)
        ft_putstr("\033[0;33;40mquote>\033[0m");
    else if (fz->mode[3] == 2)
        ft_putstr("\033[0;33;40mdquote>\033[0m");
    else if (fz->mode[3] == 3)
        ft_putstr("\033[0;33;40mpipe>\033[0m");
    else if (fz->mode[3] == 4)
        ft_putstr("\033[0;33;40mcmdand>\033[0m");
    else if (fz->mode[3] == 5)
        ft_putstr("\033[0;33;40mcmdor>\033[0m");
    else if (fz->mode[3] == 6)
        ft_putstr("\033[0;33;40mheredoc>\033[0m");
}

int     giv_last(t_froz *fz)
{
    if (fz->mode[3] == 0)
        return (3);
    else if (fz->mode[3] == 1)
        return (7);
    else if (fz->mode[3] == 2)
        return (8);
    else if (fz->mode[3] == 3)
        return (6);
    else if (fz->mode[3] == 4)
        return (8);
    else if (fz->mode[3] == 5)
        return (7);
    else if (fz->mode[3] == 6)
        return (9);
    return (3);
}

t_edit  *giv_position(t_edit *ed, int i)
{
    while (ed->rpz[0] == 0)
        ed = ed->next;
    while (ed->rpz[1] == 0)
    {
        if (ed->c[0] == '\n' && i % g_nb->tb[0] != 0)
        {
            ed->rpz[3] = i;
            ed = ed->next;
            i = (((i / g_nb->tb[0]) +1 ) * g_nb->tb[0]) + 1;
            ed->rpz[3] = i;
        }
        else
            ed->rpz[3] = i;
        ++i;
        ed = ed->next;
    }
    ed->rpz[3] = i;
    return (ed);
}



//quand prompt meme taille que fenetre init mauvais