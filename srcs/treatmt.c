#include "../twenty.h"

t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
    t_cmd   *ex;
    
    while ((*cmd)->rpz[0] == 0)
        *cmd = (*cmd)->next;
    if ((*fz)->nb[0] % g_nb->tb[0] != 1)
        ft_putchar('\n');
    if ((*cmd)->c[0] == '\0' && (*fz)->cmd == NULL) //&& (*fz)->mode[3] != 0)  // quand il n'y a rien
        return(env);
    else if (parsing(*cmd, &(*fz), &ex) == 1) // parsing good
    {
        env = launchcmd(ex, env);
        add_his(&(*hs), NULL, *fz);
        free_all_ex(&ex);
        if ((*fz)->cmd)
        {
            free((*fz)->cmd);
            (*fz)->cmd = NULL;
        }
        // free_ex(&ex);
    }
    else if ((*fz)->mode[3] == 0) // parsing error qund lauch
    {
        add_his(&(*hs), NULL, *fz);
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
    }
    return (env);
}


int     add_his(t_his **hs, t_his *nw, t_froz *fz)
{
    if (!(nw = (t_his*)malloc(sizeof(t_his))))
        return(0);
    nw->cmd = ft_strdup(fz->cmd);
    while ((*hs)->prev != NULL)
        *hs = (*hs)->prev;
    if (if_only(nw->cmd, ' ') || ((*hs)->next->cmd && ft_strcmp(nw->cmd, (*hs)->next->cmd) == 0 ))
    {
        free(nw->cmd);
        free(nw);
        return(0);
    }
    (*hs)->next->prev = nw;
    nw->next = (*hs)->next;
    nw->prev = *hs;
    (*hs)->next = nw;
    *hs = (*hs)->next;
    return (1);
}



t_env   *launchcmd(t_cmd *ex, t_env *env)
{
    t_exec     s;
    int        i;
    char       **arr;
    
    i = 0;
    s.in = 0;
    s.out = 1;
    s.ok = 1;
    while (ex->prev != NULL)
        ex = ex->prev;
        wait(0);
    if (ex->type == 42 && ex->next->type == 0 && ex->next->next->type == 42 && wait(0))   // condition si il ny qu'une commande
    {       
        wait(0);
        env = exec_fct((arr = ft_strsplit(ex->next->cmd, ' ')), env);
        free_tab(arr);
    }
    else
    {
        while (ex->next != NULL && ++i < 10)
        {
            if (ex->type != 0 && ex->type != 42)
            {
                if (ex->type == 8 || ex->type == 7)
                    env = pipe_fct(&s, ex, env);
                else if (ex->type == 9)
                    app_redirecting_out(&ex, &env, 0);
                else
                {
                    wait(0);
                    env = exec_fct((arr = ft_strsplit(ex->prev->cmd, ' ')), env);
                    free_tab(arr);
                }
            }
            if (ex->next != NULL)
                ex = ex->next;
        }
    }
    return (env);
}