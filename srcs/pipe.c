#include "../twenty.h"

void       end_pipe(t_cmd **ex, t_exec **s, t_proc *p)
{
    int     i = 0;
    int status = 0;
    
    if (p && i)
        ;
    close((*s)->p[1]);
    dup2(1, (*s)->out);
    dup2(0, (*s)->in);
    if ((*ex)->next->type == 42)
    {
        signal(SIGPIPE, sig_pipe);
        // signal(SIGCHLD, sig_child);
 
        while ((wait(&status)) > 0);
            // waitpid(0, NULL, WNOHANG);
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

// void    init_proc(t_proc *p)
// {
//     p = (t_proc*)malloc(sizeof(t_proc));
//     p->pid = 0;
//     p->next = NULL;
// }

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

t_env   *pipe_fct(t_exec *s, t_cmd **ex, t_env *env)
{
    pid_t   pid;
    t_proc  *p;
    s->in = 0;
    p = NULL;
    
    signal(SIGCHLD, sig_child);
        signal(SIGPIPE, sig_pipe);
    // ls_signal();
    while ((*ex)->next != NULL)
    {
        pipe(s->p);
        // s->out = dup(1);
        if ((pid = fork()) == -1)
            exit(EXIT_FAILURE);
        else if (pid == 0)
        {
            printf("================FILS=========================\n");
            dup2(s->in, 0);
            s->out = dup(1);
            if (pipe_on(*ex))
                dup2(s->p[1], 1);
            close(s->p[0]);
            if ((*ex)->next->type == 7 || (*ex)->next->type == 8 ||(*ex)->next->type == 9 )
                redirection(&(*ex), &env, &(*s));
            else
            {
                // ft_putstr("PUTE");
                if ((*ex)->next->type == 42)
                    waitpid(0, NULL, WNOHANG);
                else
                    wait(NULL);
                env = exec_fct_nf(ft_strsplit((*ex)->cmd, ' '), env);
            }
            // exit(0);
        }
        else
        {
            // p = add_pid(&(*p), pid);
            // wait(&pid);
            // int returnStatus;    
            // waitpid(pid, &returnStatus, 0);  // Parent process waits here for child to terminate.
            // if (returnStatus == 0)  // Verify child process terminated without error.  
            // {
            //    printf("The child process terminated normally.");    
            // }
            // if (returnStatus == 1)      
            // {
            //    printf("The child process terminated with an error!.");    
            // }
            printf("================PERE=========================\n");
            end_pipe(&(*ex), &s, &(*p));
        }
    }
        // write(1, "\r", 1);
        // wait(0);
        
    // printf("\n=========================================\n");
        //    i = free_kill(&p);
        // free_pid_loop(&(*p), i);
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
