#include "../twenty.h"

t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
    t_cmd   *ex;
    
    ex = init_ex(NULL);
    while ((*cmd)->rpz[0] == 0)
        *cmd = (*cmd)->next;
    if ((*fz)->nb[0] % g_nb->tb[0] != 1)
        ft_putchar('\n');
    if ((*cmd)->c[0] == '\0' && (*fz)->cmd == NULL && (*fz)->mode[3] != 0)  // quand il n'y a rien
        return(env);
    else if ((parsing(*cmd, &(*fz), &ex))) // parsing good
    {
        add_his(&(*hs), NULL, *fz);
        // env = launchcmd((*fz)->cmd, env);
        env = launchcmd(ex, env);
        // exit(0);  // <-------------------------
        // remplacer (*fz)->cmd en struct ex 
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
    }
    //free ex
    return (env);
}


int     add_his(t_his **hs, t_his *nw, t_froz *fz)
{
    if (!(nw = (t_his*)malloc(sizeof(t_his))))
        return(0);
    nw->cmd = ft_strdup(fz->cmd);
    while ((*hs)->prev != NULL && (*hs)->cmd != NULL)
        *hs = (*hs)->prev;
    if (if_only(nw->cmd, ' ')|| ((*hs)->next->cmd && ft_strcmp(nw->cmd, (*hs)->next->cmd) == 0 ))
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

char    **give_tab(char **ar, t_cmd **ex)
{
    int     i;
    int     e;
    t_cmd   *tmp;

    i = 0;
    tmp = *ex;
    e = -1;
    while (tmp->next != NULL && tmp->type == 0)
    {
        ++i;
        tmp = tmp->next;
    }
    if (tmp->type == 0)
        ++i;
    // printf("i = %i\n", i);
    // sleep(3);
    if (!(ar = (char**)malloc((i + 1) * sizeof(char*))))
        return (NULL);
    while (--i > -1)
    {
        ar[++e] = ft_strdup((*ex)->cmd);
        *ex = (*ex)->next;
    }
    ar[++e] = NULL;
    return (ar);
}

t_env   *launchcmd(t_cmd *ex, t_env *env)
{
    char    **ar;

    ar = NULL;
    while (ex->prev != NULL)
        ex = ex->prev;
    ar = give_tab(ar, &ex);
    env = exec_giv(ar, env);
    free(ar);
    return (env);
}

t_env	*exec_giv(char **ar, t_env *env)
{
	// else if (ft_strcmp("echo", cut[0]) == 0)
	// 	print_tab(cut, 0);
	// else if (ft_strcmp("env", cut[0]) == 0)
	// 	ecriture_info(env);
	// else if (ft_strcmp("setenv", cut[0]) == 0)
	// {
	// 	while (cut[1] && cut[++(*i)])
	// 		b_export(cut[*i], &env);
	// }
	// else if (env && ft_strcmp("unsetenv", cut[0]) == 0)
	// 	b_unset(cut, &env, 0);
	// else if (ft_strcmp("cd", cut[0]) == 0)
	// 	b_cd(cut[1], &env);
	if (ft_strcmp(ar[0], "exit") == 0) // && free_for_exit(line, cut, env))
		exit(0);
	else
		b_other(ar, env);
	// free_tab(cut);
    return (env);
}