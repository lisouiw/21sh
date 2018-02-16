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
        // printf("===TREAT APRES LAunch========\n");
        add_his(&(*hs), NULL, *fz);
        
        free_all_ex(&ex);
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
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
    while ((*hs)->prev != NULL && (*hs)->cmd != NULL)
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


t_env   *pipe_fct(t_exec *s, t_cmd *ex, t_env *env, pid_t pid)
{
    char       **arr;
    // int		new;
    
    if (wait(0) && pid == 0)
    {
        dup2(s->fd_in, 0); //change the input according to the old one
        if (ex->next->type != 42 && ex->next->type == 3 )
            dup2(s->p[1], 1);
        close(s->p[0]);
            env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env);
    }
    else
    {
        ex = ex->next;
        close(s->p[1]);
        s->fd_in = s->p[0]; //save the input for the next command
        s->fd_out = s->p[1];
        // printf("========GO===OUT===%s==%i=%i\n", ex->cmd, s->p[0], s->p[1]);
    }
    return (env);
}

t_env   *launchcmd(t_cmd *ex, t_env *env)
{
    t_exec     s;
    int        i;
    char       **arr;
    
    i = 0;
    s.fd_in = 0;
    while (ex->prev != NULL)
        ex = ex->prev;
    if (ex->type == 42 && ex->next->type == 0 && ex->next->next->type == 42)   // condition si il ny qu'une commande
    {       
        env = exec_fct((arr = ft_strsplit(ex->next->cmd, ' ')), env);
        free_tab(arr);
    }
    else
    {
        while (ex->next != NULL && ++i < 10)
        {
            if (ex->type != 0 && ex->type != 42)
            {
                if (ex->type == 8)
                    redirecting_out(&ex, &env, 0);
                else if (ex->type == 7)
                    redirecting_in(&ex, &env, 0);
                else if (ex->type == 9)
                    app_redirecting_out(&ex, &env, 0);
            }
            if (ex->next != NULL)
                ex = ex->next;
        }
    }
    return (env);
}