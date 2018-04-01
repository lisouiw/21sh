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

void    redirection_no_cmd(t_cmd **ex, t_env **env, t_exec *s) //redirection for pipe
{
    s->in = dup(0);
    s->out = dup(1);
    if (redirection_check_create(*ex))
        redirecting_exec(ex, env, NULL, s);
    dup2(/*1, */s->out, 1);
    dup2(/*0,*/ s->in, 0);
    while ((*ex)->type >= 6 && (*ex)->type <= 11)
		*ex = (*ex)->next;
}

void     move_on(t_cmd **ex, int i)
{
	*ex = (*ex)->next;
    if (i == 4)
        while ((*ex)->type != 3 && (*ex)->type != 5 && (*ex)->type != 13 && (*ex)->type != 42)
	        *ex = (*ex)->next;
    else if (i == 5)
        while ((*ex)->type != 3 && (*ex)->type != 4 && (*ex)->type != 13 && (*ex)->type != 42)
	        *ex = (*ex)->next;
    // printf("cmd = %s && type = %i\n", (*ex)->cmd, (*ex)->type);
    // sleep(3);
}

t_env   *launchcmd(t_cmd *ex, t_env *env)
{
    t_exec  s;
    char    **arr;

    init_launch(&s, &ex);
    while (ex->next != NULL)
    {
        // printf("cmd = %s && type = %i ok = %i\n", ex->cmd, ex->type, s.ok);
        if (pipe_on(ex)) //je vais avoir des pipes a exec
            env = pipe_fct(&s, &ex, env);
        else if ( ex->type == 4 && s.ok == 0) // &&
            move_on(&ex, 4);
        else if ( ex->type == 5 && s.ok == 1) // ||
            move_on(&ex, 5);
        else if (ex->type == 0 && !(ex->next->type >= 6 && ex->next->type <= 11))
        {
            env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env, &s);
            free_tab(arr);
            ex = ex->next;
        }
        else if (ex->type == 0 && ex->next->type >= 6 && ex->next->type <= 11)
            redirection_fork(&ex, &env, &s);
        else if (ex->type >= 6 && ex->type <= 11)
            redirection_no_cmd(&ex, &env, &s);
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