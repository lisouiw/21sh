#include "../twenty.h"

void       end_pipe(t_cmd **ex, t_exec **s, t_proc *p)
{
    // int     i;

    
    if (p)
        ;
    close((*s)->p[1]);
    if ((*ex)->next->type == 42)
    {
        // kill (wait(NULL), 0);
        wait(0);
        dup2(1, (*s)->out);
        dup2(0, (*s)->in);
        // dup2((*s)->out, 1);
    }
    // if ((*ex)->next->type == 42)
    // {
    //     i = free_kill(&p);
    //     free_pid_loop(&(*p), i);
    // }
    // if ((*ex)->next->type == 42)
    //     wait(0);
    if ((*ex)->next->type == 7)
        while ((*ex)->type == 7 || (*ex)->next->type == 7 || (*ex)->type == 3)
            *ex = (*ex)->next;
    else if ((*ex)->next->next != NULL)
        *ex = (*ex)->next->next;
    else if ((*ex)->next != NULL)
        *ex = (*ex)->next;
    (*s)->in = (*s)->p[0];
}

int     pipe_on(t_cmd *ex)
{
    while (ex->type != 3 && ex->type != 4 && ex->type != 5 && ex->type != 13 && ex->type != 42)
            ex = ex->next;
    if (ex->type == 3)
        return (1);
    return (0);
}

void    init_proc(t_proc *p)
{
    p = (t_proc*)malloc(sizeof(t_proc));
    p->pid = 0;
    p->next = NULL;
}

t_proc  *add_pid(t_proc *p, pid_t pid)
{
    t_proc  *nw;
    t_proc  *tmp;
    
    if (p == NULL)
    {
        p = (t_proc*)malloc(sizeof(t_proc));
        p->pid = pid;
        p->next = NULL;
    }
    else
    {
        tmp = p;
        while (tmp->next != NULL)
            tmp = tmp->next;
        nw = (t_proc*)malloc(sizeof(t_proc));
        nw->pid = pid;
        nw->next = NULL;
        tmp->next = nw;
    }
    return (p);
}
void	sig_pipe(int sig)
{
    sig = 0;
    printf("PIPEPUTE\n");
}
void	sig_int(int sig)
{
    sig = 0;
    exit(0);
}
void	sig_quite(int sig)
{
    printf("INTPUTE %i\n", sig);
    exit(0);
}

void	sig_child(int sig)
{
    char    buf[1];

    sig = 0;
    kill (wait(NULL), 0);
    printf("wait = %i\n", waitpid(-1, NULL, WNOHANG));
    if (waitpid(-1, NULL, WNOHANG) == -1)
        return;

    while (42)
    {
        read(1 , &buf,1);
        if (buf[0] == '\n')
        {
            exit(0);
            // kill (wait(NULL), 0);
        }
        if (waitpid(-1, NULL, WNOHANG) == -1)
            return;
        buf[0] = '\0';
    }
}

void	ls_signal(void)
{
    signal(SIGPIPE, sig_pipe);
    signal(SIGINT, sig_int);
    signal(SIGILL, sig_quite);
	signal(SIGTSTP, sig_quite);
	signal(SIGCONT, sig_quite);
    signal(SIGQUIT,sig_quite);
	signal(SIGABRT,sig_quite);
	signal(SIGKILL,sig_quite);
	signal(SIGTERM,sig_quite);
	signal(SIGUSR1,sig_quite);
	signal(SIGUSR2,sig_quite);

    signal(SIGSTOP,sig_quite);
	signal(SIGTSTP,sig_quite);
	signal(SIGTTIN	,sig_quite);
	signal(SIGTTOU,sig_quite);
	signal(SIGQUIT,sig_quite);
	signal(SIGQUIT,sig_quite);
    
    // SIGCONT	19,18,25	Cont	Continuer si arrêté.
   
}

t_env   *pipe_fct(t_exec *s, t_cmd **ex, t_env *env)
{
    // SIGPIPE
    pid_t   pid;
    t_proc  *p;
    int i = 0;
    s->in = 0;
    p = NULL;

    
    ls_signal();
    while ((*ex)->next != NULL && ++i< 5)
    {
        s->out = dup(1);
        pipe(s->p);
        if ((pid = fork()) == -1)
            exit(EXIT_FAILURE);
        else if (pid == 0)
        {
            dup2(s->in, 0);
            s->out = dup(1);
            if (pipe_on(*ex))
                dup2(s->p[1], 1);
            close(s->p[0]);
            if ((*ex)->next->type == 7 || (*ex)->next->type == 8 ||(*ex)->next->type == 9 )
                redirection(&(*ex), &env, &(*s));
            else
                env = exec_fct_nf(ft_strsplit((*ex)->cmd, ' '), env);
        }
        else
        {
            p = add_pid(&(*p), pid);
            end_pipe(&(*ex), &s, &(*p));
        }
    }
    printf("PIPE SORTIE\n");
    return (env);
}

// void    loop_pipe(char ***cmd) //ls 3< "."
// {
//     int		p[2];
// 	pid_t   pid;
// 	int		fd_in = 0;
    
//     while (*cmd != NULL)
//     {
//         pipe(p);
//         if ((pid = fork()) == -1)
//             exit(EXIT_FAILURE);
//         else if (pid == 0)
//         {
//              dup2(fd_in, 0);
// 			    if (*(cmd + 1) != NULL)
// 				    dup2(p[1], 1);
//              close(p[0]);
//              execvp((*cmd)[0], *cmd);
//         }
//         else
//         {
//              wait(NULL);
//              close(p[1]);
// 			    fd_in = p[0];
//              ++cmd;
//         }
//     }
// }

// t_env   *pipe_fct(t_exec *s, t_cmd *ex, t_env *env)
// {
//     // char       **arr;
// 	pid_t   pid;
    
//     pipe(s->p);
//     if ((pid = fork()) == -1)
//         exit(EXIT_FAILURE);
//     else if (pid == 0)
//     {
//         dup2(s->in, 0); 
//         if (ex->next->type == 3 || ex->next->type == 7 || ex->next->type == 8 || ex->next->type == 9)
//             dup2(s->p[1], 1);
//         if (ex->type == 8)
//             redirecting_out_child(&ex, &env, 0, &pid, &(*s));
//         else if (ex->type == 7)
//             redirecting_in_child(&ex, &env, 0, &pid, &(*s));
//         // else
//         //     env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env);
//     }
//     else
//     {
//         wait(0);
//         if (ex->type == 8)
//             printf("PIPE_FCT[8] in = %i && out = %i\n", s->in, s->out);
//         else if (ex->type == 7)
//         {
//             s->out = s->p[1];
//             close (s->p[0]);
//             printf("PIPE_FCT[7] in = %i && out = %i\n", s->in, s->out);
//         }
//         else
//             printf("PIPE_FCT[other] in = %i && out = %i\n", s->in, s->out);
        
//         sleep(1);
//     }
//     return (env);
// }
