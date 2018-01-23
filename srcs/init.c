#include "../twenty.h"

t_his   *init_hs(t_his *hs, t_his *next)
{
    if (!(hs = (t_his*)malloc(sizeof(t_his))))
        return(NULL);
    if (!(next = (t_his*)malloc(sizeof(t_his))))
        return(NULL);
    hs->cmd = NULL;
    next->cmd = NULL;
    next->prev = hs;
    next->next = NULL;
    hs->next = next;
    hs->prev = NULL;
    return (hs);
}

t_num   *init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs)
{
    struct ttysize	ts;

    set_up_term();
    tputs(tgetstr("cl", NULL), 0, ft_put);
    *env = give_env(NULL);
    *ed = init_edit(NULL);
    *fz = init_fz(NULL);
    *hs = init_hs(NULL, NULL);
    tputs(tgetstr("sc", NULL), 0, ft_put);
    ft_putstr("\033[0;33;40m>>\033[0m");
    if (!(g_nb = (t_num*)malloc(sizeof(t_num))))
        return (NULL);
    ioctl(1, TIOCGSIZE, &ts);
    g_nb->tb[0] = ts.ts_cols;
	g_nb->tb[1] = ts.ts_lines;
    return (g_nb);
}

t_froz      *init_fz(t_froz *fz)
{
    if (!(fz = (t_froz*)malloc(sizeof(t_froz))))
        return (NULL);
    fz->buf[0] = 0;
    fz->buf[1] = 0;
    fz->buf[2] = 0;
    fz->mode[0] = 0;
    fz->mode[1] = 0;
    fz->mode[2] = 1;
    fz->mode[3] = 0;
    fz->nb[0] = 3;
    fz->paste = NULL;
    fz->cmd = NULL;
    return (fz);
}

void    init_data(t_froz **fz)
{
    (*fz)->buf[0] = 0;
    (*fz)->buf[1] = 0;
    (*fz)->buf[2] = 0;
}

void    init_for_new(t_his **hs, t_froz **fz, t_edit **ed)
{
    tputs(tgetstr("sc", NULL), 0, ft_put);
    put_prompt_init(&(*fz));
    free_ed(&(*ed), *fz);
    (*fz)->mode[0] = 0;
    (*fz)->mode[1] = 0;
    (*fz)->mode[2] = 1;
    // free((*fz)->cmd);
    // (*fz)->cmd = NULL;
    if (*hs == NULL)
        return;
    while ((*hs)->prev != NULL && (*hs)->cmd != NULL)
        *hs = (*hs)->prev;
}