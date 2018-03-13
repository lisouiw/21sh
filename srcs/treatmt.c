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
    else if (parsing(*cmd, &(*fz), &ex, env) == 1) // parsing good
    {
        add_his(&(*hs), NULL, *fz);
        env = launchcmd(ex, env);
        free_all_ex(&ex);
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
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
    t_exec  dot;
    char    **arr;

    init_launch(&dot, &ex);
    while (ex->next != NULL)
    {
        if (pipe_on(ex)) //je vais avoir des pipes a exec
        {
            signal(SIGPIPE, sig_pipe);
            env = pipe_fct(&dot, &ex, env);
        }
        else if (ex->type == 0 && (ex->next->type != 7 && ex->next->type != 8 && ex->next->type != 9))
        {
            env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env);
            free_tab(arr);
            ex = ex->next;
        }
        else if (ex->type == 0 && (ex->next->type == 7 || ex->next->type == 8  || ex->next->type == 9))
            redirection_f(&ex, &env, &dot);
        else
            ex = ex->next;
        // if (ex->type != 0)
        //     dot.cmd = ex->type;
        // if (ex->type == 0 && ex->next->type != 3 && ex->next->type != 7 && ex->next->type != 8 && ex->next->type != 9 && dot.cmd != 3)
        //     env = exec_fct(ft_strsplit(ex->cmd, ' '), env);
        // else if (ex->type == 0 && ex->next->type == 3)
        // printf("Cmd = %s\n", ex->cmd);
    }
    return (env);
}