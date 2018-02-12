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
        add_his(&(*hs), NULL, *fz);
        env = launchcmd(ex, env);
        wait(0);
        free((*fz)->cmd);
        (*fz)->cmd = NULL;
        free_ex(&ex);
    }
    else if ((*fz)->mode[3] == 0) // parsing error qund lauch
    {
        add_his(&(*hs), NULL, *fz);
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
    e = -1;
    tmp = *ex;
    while (tmp->next != NULL && tmp->type == 0)
    {
        ++i;
        tmp = tmp->next;
    }
    if (tmp->type == 0)
        ++i;
    if (!(ar = (char**)malloc((i + 1) * sizeof(char*))))
        return (NULL);
    while (--i > -1)
    {
        ar[++e] = ft_strdup((*ex)->cmd);
        *ex = (*ex)->next;
    }
    ar[i] = NULL;
    return (ar);
}

t_env   *pipe_fct(t_exec *s, t_cmd *ex, t_env *env, pid_t pid)
{
    char       **arr;
    
    if (wait(0) && pid == 0)
    {
        dup2(s->fd_in, 0); //change the input according to the old one
        if (ex->next->type != 42 && ex->next->type == 3)
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
        printf("========GO===OUT===%s==%i=%i\n", ex->cmd, s->p[0], s->p[1]);
    }
    return (env);
}

t_env   *launchcmd(t_cmd *ex, t_env *env)
{
    pid_t      pid;
    int        i = 0;
    t_exec     s;

    s.fd_in = 0;
    while (ex->prev != NULL)
        ex = ex->prev;
    // print_ex(ex);
    while (ex->next != NULL && ++i < 10)
    {
        if (ex->type == 0)
        {
            pipe(s.p);
            printf("========GO====%s=====\n", ex->cmd);
            if ((pid = fork()) == -1)
                exit(EXIT_FAILURE);
            env = pipe_fct(&s, ex, env, pid);
        }
        if (ex->next != NULL)
            ex = ex->next;
    }
    exit(0);
    return (env);
}




// void  pipe(char **cmd)           
// {
//   int   p[2];
//   int   fd_in = 0;

//   while (*cmd != NULL)
//     {
//       pipe(p);
//       else if (pid == 0)
//         {
//           printf("fd = %i && p[0] = %i && p[1] = %i\n", fd_in, p[0], p[1]);
//         	dup2(fd_in, 0); //change the input according to the old one 
//           if (*(cmd + 1) != NULL)
//             dup2(p[1], 1);
//           close(p[0]);
//           execvp((*cmd)[0], *cmd);
//           exit(EXIT_FAILURE);
//         }
//       else
//         {
//           wait(NULL);
//           close(p[1]);
//           fd_in = p[0]; //save the input for the next command
//           printf("fd = %i && p[0] = %i && p[1] = %i\n=========================\n", fd_in, p[0], p[1]);
//           cmd++;
//         }
//     }
// }






t_env	*exec_fct(char **ar, t_env *env)
{
	if (ft_strcmp("echo", ar[0]) == 0)
		print_tab(ar, 0);
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
	else if (ft_strcmp(ar[0], "exit") == 0) // && free_for_exit(line, cut, env))
		exit(0);
    else
		b_other_nf(ar, env);
		// b_other(ar, env);
        
    return (env);
}














// fonction
// {
//     char    ***arr;

//     if (!(arr = (char ***)malloc(len *sizeof(char**))))
//         return (NULL);
//     i = -1;
//     while (++i < len)
//     {
//         arr[i] = give_tab();
//     }
//     arr[i] = NULL
// }

// give_tab
// {
//     char **arr;

//     if (!(arr = (char **)malloc(len * sizeof(char*)))
//         return (NULL);
//     i = -1;
//     while (++i < len)
//     {
//         arr[i] = strdup(str);
//     }
//     arr[i] = NULL
//     return (arr);
// }