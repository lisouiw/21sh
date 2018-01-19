#include "../twenty.h"

void    free_ed(t_edit **ed)
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
    (*ed)->rpz[2] = 3;
    (*ed)->prev = *ed;
    (*ed)->next = *ed;
}

int         main(void)
{
    t_froz  *fz;
    t_env   *env;
    t_edit  *ed;
    t_his   *hs;

    g_nb = init_shell(&fz, &env, &ed, &hs);
    while (42)
    {
        read(0, &fz->buf, 4);
        // printf("%i %i %i\n", fz->buf[0], fz->buf[1], fz->buf[2]);
        // exit(0);
        if (fz->buf[0] == 10)
        {
            cursor_end(fz);

            env = treat_cmd(env, &ed, &hs, fz);
            tputs(tgetstr("sc", NULL), 0, ft_put);
            ft_putstr("\033[0;33;40m>>\033[0m");
            free_ed(&ed);     
            init_for_new(&hs, &fz);
            
        }
        else
            ed = touch(ed, fz, hs);
        init_data(&fz);
    }
}

void    cursor_end(t_froz *fz)
{
    int     i;
    
    tputs(tgetstr("rc", NULL), 0, ft_put);
    i = fz->nb[0];
    if (i % g_nb->tb[0] == 1)
	    ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(g_nb->tb[0]), "D")));
    else
	    ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(g_nb->tb[0]), "C")));
	if (i > g_nb->tb[0] && i % g_nb->tb[0] == 0)
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((i / g_nb->tb[0]) - 1),"B")));
	else if (i > (g_nb->tb[0]))
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((i / g_nb->tb[0])),"B")));
}

t_num   *init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs)
{
    struct ttysize	ts;

    set_up_term();
    tputs(tgetstr("cl", NULL), 0, ft_put);
    *env = give_env(NULL);
    *ed = init_edit(NULL);
    *fz = init_fz(NULL);
    *hs = NULL;
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
    fz->nb[0] = 3;
    return (fz);
}

void    init_data(t_froz **fz)
{
    (*fz)->buf[0] = 0;
    (*fz)->buf[1] = 0;
    (*fz)->buf[2] = 0;
}

void    init_for_new(t_his **hs, t_froz **fz)
{
    (*fz)->nb[0] = 3;
    (*fz)->mode[0] = 0;
    (*fz)->mode[1] = 0;
    (*fz)->mode[2] = 1;
    if (*hs == NULL)
        return;
    while ((*hs)->prev != NULL)
        *hs = (*hs)->prev;
}