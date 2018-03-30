#include "../twenty.h"

t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
    t_cmd   *ex;
    
    ex = NULL;
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
    t_exec  s;
    char    **arr;

    init_launch(&s, &ex);
    while (ex->next != NULL)
    {
        // printf("cmd = %s && type = %i\n", ex->cmd, ex->type);
        if (pipe_on(ex)) //je vais avoir des pipes a exec
            env = pipe_fct(&s, &ex, env);
        // else if ( ex->prev->type == 4 && s.ok == 0)
        // {
        //     ex = ex->next;
        //     // while (ex->prev->type == 4)
        // }
        else if (ex->type == 0 && !(ex->next->type >= 6 && ex->next->type <= 11))
        {
            env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env, &s);
            free_tab(arr);
            ex = ex->next;
        }
        else if (ex->type == 0 && ex->next->type >= 6 && ex->next->type <= 11)
            redirection_fork(&ex, &env, &s);
        // else if (ex->type >= 6 && ex->type <= 11)
        // {
        //     redirection_no_cmd(&ex, &env, &s);
            
        //     // printf("JE ME SUIS PERDU\n");
        //     while (ex->type >= 6 && ex->type <= 11)
        //         ex = ex->next;
        // }
        else
            ex = ex->next;
    }
    return (env);
}


























        // if (ex->type != 0)
        //     s.cmd = ex->type;
        // if (ex->type == 0 && ex->next->type != 3 && ex->next->type != 7 && ex->next->type != 8 && ex->next->type != 9 && s.cmd != 3)
        //     env = exec_fct(ft_strsplit(ex->cmd, ' '), env);
        // else if (ex->type == 0 && ex->next->type == 3)
        // printf("Cmd = %s\n", ex->cmd);