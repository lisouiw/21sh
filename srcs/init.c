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

t_num   *init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs) //init start all struct
{
    struct ttysize	ts;

    if ((*env = give_env(NULL)) == NULL)
    {
        ft_putstr_fd("Need An Environment\n", 2);
        exit(0);
    }
    set_up_term();
    tputs(tgetstr("cl", NULL), 0, ft_put);
    *ed = init_edit(NULL);
    *hs = init_hs(NULL, NULL);
    *fz = init_fz(NULL);
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
    if (!(fz->here = (t_here*)malloc(sizeof(t_here))))
        return (NULL);
    fz->here->next = NULL;
    fz->here->prev = NULL;
    fz->here->delim = NULL;
    fz->here->ok[0] = 0;
    return (fz);
}

void    init_data(t_froz **fz)
{
    (*fz)->buf[0] = 0;
    (*fz)->buf[1] = 0;
    (*fz)->buf[2] = 0;
}

void    init_for_new(t_his **hs, t_froz **fz, t_edit **ed) //init for next exec
{
    // if ( (*fz)->mode[3] == 0)
    // {
    //     int     status;
    //     wait(&status);
    //     // printf("%i | %i | %i | %i | %i | %i | %i| %i\n",WIFEXITED(status),WEXITSTATUS(status),WIFSIGNALED(status),WTERMSIG(status),WCOREDUMP(status),WIFSTOPPED(status),WSTOPSIG(status),WIFCONTINUED(status));
    // }
    int     status;
    wait(&status);
    // wait(0);
    (*fz)->mode[3] == 0 ? set_up_term() : set_up_term_prompt();
    wait(0);
    tputs(tgetstr("sc", NULL), 0, ft_put);
    wait(0);
    put_prompt_init(&(*fz));
    free_ed(&(*ed), *fz);
    (*ed)->rpz[2] = giv_last(*fz);
    (*ed)->rpz[3] = giv_last(*fz);
    free_init_fz(*fz);
    if (*hs == NULL)
        return;
    while ((*hs)->prev != NULL)
        *hs = (*hs)->prev;
    wait(0);
}

t_cmd   *init_ex(t_cmd *ex)
{
    if (!(ex = (t_cmd*)malloc(sizeof(t_cmd))))
        return (NULL);
    ex->cmd = NULL;    
    ex->type = 0;
    if (!(ex->prev = (t_cmd*)malloc(sizeof(t_cmd))))
        return (NULL);
    ex->prev->cmd = NULL;
    ex->prev->prev = NULL;
    ex->prev->type = 42;
    ex->prev->start = 0;
    ex->prev->next = ex;    

    if (!(ex->next = (t_cmd*)malloc(sizeof(t_cmd))))
        return (NULL);
    ex->next->cmd = NULL;    
    ex->next->next = NULL;
    ex->next->prev = ex;
    ex->next->type = 42;
    ex->next->start = 0;
    return (ex);
}

void    init_launch(t_exec *dot, t_cmd **ex)
{
    while ((*ex)->prev != NULL)
        *ex = (*ex)->prev;
    *ex = (*ex)->next;
    dot->cmd = 0;
    dot->out = 1;
    dot->in = 0;
    dot->ok = 1;
}
