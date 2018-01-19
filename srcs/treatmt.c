#include "../twenty.h"

t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz *fz)
{
    while ((*cmd)->rpz[0] == 0)
        *cmd = (*cmd)->next;
    if ((*cmd)->c[0] == '\0') // quand il n'y a rien
    {
        ft_putchar('\n');
        return(env);
    }
    else if (1) // parsing good
    {
        if (fz->nb[0] % g_nb->tb[0] != 1)
            ft_putchar('\n');
        if (add_his(*cmd, hs, NULL, fz))
            env = launchcmd(hs, env);

    }
    else //parsing no good
        ;
    return (env);
}


int     add_his(t_edit *cmd, t_his **hs, t_his *nw, t_froz *fz)
{
    int     i;

    i = -1;
    fz->nb[0] = fz->nb[0] - 3;
    if (!(nw = (t_his*)malloc(sizeof(t_his))))
        return(0);
    if (!(nw->cmd = (char*)malloc((fz->nb[0] + 1)* sizeof(char))))
        return (0);
    while (++i < fz->nb[0])
    {
        nw->cmd[i] = cmd->c[0];
        cmd = cmd->next;
    }
    nw->cmd[i] = '\0';
    if (if_only(nw->cmd, ' '))
    {
        free(nw->cmd);
        free(nw);
        return(0);
    }
    if (*hs == NULL)
    {
        nw->next = NULL;
        nw->prev = NULL;
    }
    else
    {
        while ((*hs)->prev != NULL)
            *hs = (*hs)->prev;
        nw->next = *hs;
        nw->prev = (*hs)->prev;
        (*hs)->prev = nw;
    }
    *hs = nw;
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
	// else if (ft_strcmp(line, "exit") == 0 && free_for_exit(line, cut, env))
	// 	exit(0);
	else
		b_other(cut, env);
	// free_tab(cut);
    return (env);
}