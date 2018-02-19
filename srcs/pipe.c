#include "../twenty.h"

t_env   *pipe_fct(t_exec *s, t_cmd *ex, t_env *env)
{
    // char       **arr;
	pid_t   pid;
    
    pipe(s->p);
    if ((pid = fork()) == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
    {
        dup2(s->in, 0); 
        if (ex->next->type == 3 || ex->next->type == 7 || ex->next->type == 8 || ex->next->type == 9)
            dup2(s->p[1], 1);
        if (ex->type == 8)
            redirecting_out_child(&ex, &env, 0, &pid, &(*s));
        else if (ex->type == 7)
            redirecting_in_child(&ex, &env, 0, &pid, &(*s));
        // else
        //     env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env);
    }
    else
    {
        wait(0);
        if (ex->type == 8)
            printf("PIPE_FCT[8] in = %i && out = %i\n", s->in, s->out);
        else if (ex->type == 7)
        {
            s->out = s->p[1];
            close (s->p[0]);
            printf("PIPE_FCT[7] in = %i && out = %i\n", s->in, s->out);
        }
        else
            printf("PIPE_FCT[other] in = %i && out = %i\n", s->in, s->out);
        
        sleep(1);
    }
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

