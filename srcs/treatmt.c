#include "../twenty.h"

t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
    t_cmd   *ex;

    while ((*cmd)->rpz[0] == 0) // Go debut de la liste
        *cmd = (*cmd)->next;
    if ((*fz)->nb[0] % g_nb->tb[0] != 1) //eviter de fausser les calcul
        ft_putchar('\n');
    if ((*cmd)->c[0] == '\0' || (if_only_i(ed_str(*cmd, NULL, (*fz)->nb[0] - giv_last(*fz)),' ') && (*fz)->cmd == NULL)) //&& (*fz)->mode[3] != 0)  // quand il n'y a rien
        return(env);
    else if (parsing(*cmd, *fz, &ex, env) == 1) // parsing. OK go loop
    {
        add_his(hs, NULL, *fz); //ajout historique
        // print_ex_up(ex);
        env = launchcmd(ex, env);   
        free_all_ex(&ex);
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
    }
    else if ((*fz)->mode[3] == 0) // parsing error attend d'etre completer
    {
        add_his(hs, NULL, *fz);
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
    }
    return (env);
}


void     add_his(t_his **hs, t_his *nw, t_froz *fz)
{
    if (!(fz->cmd && (nw = (t_his*)malloc(sizeof(t_his)))))
        return;
    nw->cmd = ft_strdup(fz->cmd);
    while ((*hs)->prev != NULL)
        *hs = (*hs)->prev;
    if (if_only(nw->cmd, ' ') || ((*hs)->next->cmd && ft_strcmp(nw->cmd, (*hs)->next->cmd) == 0 ))
    {
        free(nw->cmd);
        free(nw);
        return ;
    }
    (*hs)->next->prev = nw;
    nw->next = (*hs)->next;
    nw->prev = *hs;
    (*hs)->next = nw;
    *hs = (*hs)->next;
}


t_env   *launchcmd(t_cmd *ex, t_env *env)
{
    t_exec  dot;
    char    **arr;

    init_launch(&dot, &ex);
    while (ex->next != NULL)
    {
        printf("cmd = %s && type = %i\n", ex->cmd, ex->type);
        if (pipe_on(ex)) //je vais avoir des pipes a exec
            env = pipe_fct(&dot, &ex, env);
        else if (ex->type == 0 && !(ex->next->type >= 6 && ex->next->type <= 11))
        {
            env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env);
            free_tab(arr);
            ex = ex->next;
        }
        else if (ex->type == 0 && ex->next->type >= 6 && ex->next->type <= 11)
            redirection_fork(&ex, &env, &dot);
        else
            ex = ex->next;
    }
    return (env);
}


























        // if (ex->type != 0)
        //     dot.cmd = ex->type;
        // if (ex->type == 0 && ex->next->type != 3 && ex->next->type != 7 && ex->next->type != 8 && ex->next->type != 9 && dot.cmd != 3)
        //     env = exec_fct(ft_strsplit(ex->cmd, ' '), env);
        // else if (ex->type == 0 && ex->next->type == 3)
        // printf("Cmd = %s\n", ex->cmd);