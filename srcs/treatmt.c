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
        printf("CMD_>%s\n", (*fz)->cmd);
        // print_ex(ex);
        // exit(0);
        add_his(&(*hs), NULL, *fz);
        env = launchcmd(ex, env);
        // printf("===TREAT APRES LAunch========\n");
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
        free_ex(&ex);
    }
    else if ((*fz)->mode[3] == 0) // parsing error qund lauch
    {
        add_his(&(*hs), NULL, *fz);
        (*fz)->cmd = NULL;
    }
    // printf("MODE = %i\n", (*fz)->mode[3]);
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
    pid_t      pid = 0;
    int        i;
    char       **arr;
    int		    new;
    t_cmd         *tmp;


    // puts("COUCOU\n");
    // return (env);
    
    
    i = 0;
    s.fd_in = 0;
    while (ex->prev != NULL)
        ex = ex->prev;
    if (ex->type == 42 && ex->next->type == 0 && ex->next->next->type == 42)   // condition si il ny qu'une commande
    {         
        // if ((pid = fork()) == -1)
        //     exit(EXIT_FAILURE);
        // else if (wait(0) && pid == 0)
            env = exec_fct((arr = ft_strsplit(ex->next->cmd, ' ')), env);
    //     else
    //         wait(0);
    }
    else
    {
        while (ex->next != NULL && ++i < 10)
        {
            if (ex->type != 0 && ex->type != 42)
            {
                if (ex->type == 8)
                {
                    pid = 0;
                    if ((pid = fork()) == -1)
                        exit(EXIT_FAILURE);
                    else if (pid == 0)
                    {
                        arr = ft_strsplit(ex->cmd, ' ');
                        if (arr[2] == NULL)
                            new = open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                        else 
                            new = open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                        i = dup(1);
                        dup2(new, 1);
                        tmp = ex;
                        free_tab(arr);
                        while (tmp->prev->type !=0  && tmp->prev->type != 42)
                            tmp = tmp->prev;
                        if (wait(0) && tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')))
                            env = exec_fct_nf(arr, env);
                    }
                    else
                    {
                        wait(0);
                        close(new);
                        dup2(1, i);
                        
                    }
                }
            }
            if (ex->next != NULL)
                ex = ex->next;
        }
        
    }
    return (env);
}

t_env	*exec_fct_nf(char **cut, t_env *env)
{
    if (ft_strcmp("echo", cut[0]) == 0)
        print_tab(cut, 0);
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
	else if (ft_strcmp(cut[0], "exit") == 0) // && free_for_exit(line, cut, env))
    {
        printf("exit\n");
        exit(0);
    }
    else
		b_other_nf(cut, env);
		// b_other(ar, env);
    return (env);
}

t_env	*exec_fct(char **cut, t_env *env)
{
    if (ft_strcmp("echo", cut[0]) == 0)
        print_tab(cut, 0);
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
	else if (ft_strcmp(cut[0], "exit") == 0) // && free_for_exit(line, cut, env))
		exit(0);
    else
		b_other(cut, env);
		// b_other(ar, env);
    return (env);
}
