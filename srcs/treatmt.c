#include "../twenty.h"

t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
    while ((*cmd)->rpz[0] == 0)
        *cmd = (*cmd)->next;
    if ((*fz)->nb[0] % g_nb->tb[0] != 1)
        ft_putchar('\n');
    if ((*cmd)->c[0] == '\0' && (*fz)->cmd == NULL) // quand il n'y a rien
        return(env);
    else if ((parsing(*cmd, &(*fz)))) // parsing good
    {
        add_his(&(*hs), NULL, *fz);
        env = launchcmd(hs, env);
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
    }
    else //parsing no good
    {
        // (*fz)->cmd = ed_str(*cmd, *fz, NULL);
        // quote
        // dquote
        // pipe
        // cmdand
        // cmdor
        // heredoc
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


t_env   *launchcmd(t_his **cmd, t_env *env)
{
    int     i;

    i = 0;
    env = exec_giv((*cmd)->cmd, env, NULL, &i);
    return (env);
}

t_env	*exec_giv(char *line, t_env *env, char **cut, int *i)
{
	i = 0;
	if (!(cut = ft_strsplit(line, ' ')) || !cut[0])
		;
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
	else if (ft_strcmp(line, "exit") == 0 && free_for_exit(line, cut, env))
		exit(0);
	else
		b_other(cut, env);
	// free_tab(cut);
    return (env);
}