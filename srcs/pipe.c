#include "../twenty.h"
#include <unistd.h>

void       end_pipe(t_cmd **ex, t_exec **s, int pp)
{
    if (ex)
        ;
    signal(SIGCHLD, SIG_DFL);
    close((*s)->p[1]);
    dup2(1, (*s)->out);
    dup2(0, (*s)->in);
    if (pp == 0)
    {
        wait(0);
    }
    // while ((*ex)->type != 3 && (*ex)->type != 4 && (*ex)->type != 5 && (*ex)->type != 13 && (*ex)->type != 42)
    //         *ex = (*ex)->next;
    (*s)->in = (*s)->p[0];
}

int     pipe_on(t_cmd *ex)
{
    while (ex->type != 3 && ex->type != 4 && ex->type != 5 && ex->type != 13 && ex->type != 42)
            ex = ex->next;
    if (ex->type == 3 && ex->next->type == 0)
    {
        ex = ex->next;
        return (1);
    }
    else if (ex->type == 3)
        return (1);
    return (0);
}

t_env   *pipe_fct(t_exec *s, t_cmd **ex, t_env *env)
{
    int     i= 0;
    int     pp = 1;
    pid_t   pid;
    
    s->in = 0;
    while (pp == 1)
    {
        s->out = dup(1);
        pp = pipe_on(*ex);
        if ((*ex)->cmd == NULL)
            return(env);
        pipe(s->p);
        if (!((*ex)->type >= 6 && (*ex)->type <= 11))
                *ex = (*ex)->next;
        else if (!(((*ex)->next->type >= 6 && (*ex)->next->type <= 11) || ((*ex)->type == 0 || ((*ex)->type >= 6 && (*ex)->type <= 11))))
                *ex = (*ex)->next;
        else if (!((*ex)->type >= 6 && (*ex)->type <= 11 )&& (pid = fork()) == -1)
            exit(-1);
        else if (pid == 0)   /////////////////////////////CHILD///////////////////////////
        {
            dup2(s->in, 0);
            if (pp)
                dup2(s->p[1], 1);
            close(s->p[0]);
            if ((*ex)->type >= 6 && (*ex)->type <= 11)
                redirection_no_cmd(ex, &env, &(*s));
            else if ((*ex)->next->type >= 6 && (*ex)->next->type <= 11)
                redirection(ex, &env, &(*s));
            else if ((*ex)->type == 0)
                env = exec_fct_nf(ft_strsplit((*ex)->cmd, ' '), env, ex, s);
        }
        else  //////////////////////PARENT////////////////////////////////
        {
         
            if (pp == 0) //derniere commande./
                wait(NULL);
            end_pipe(&(*ex), &s, pp);
        }
        if (++i > 10)
            exit(0);
    }
    // wait(0);
    return (env);
}


        // wait(&status);       /*you made a exit call in child you 
        //                    need to wait on exit status of child*/
        // if(WIFEXITED(status))
        // //     exit(0);
        // if (WEXITSTATUS(status))
        //     exit(0);

        // printf("child exited with = %d || %d",W