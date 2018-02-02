#include "../twenty.h"

void    execution(t_env **env, t_cmd *ex, t_exec **exec, int a)
{
    if (a == 3)
    {
    }
    exit(0);
}


void    pipe(void)
{
    return;
}

// void    pipe_fct(t_env **env, t_cmd *ex, t_exec **exec)
// {
//     int		p[2];
// 	pid_t   pid;
//     int		fd_in = 0;
//     char    **tab;
    
//     pipe(p);
//     if ((pid = fork()) == -1)
//         exit(EXIT_FAILURE);
//     else if (pid == 0)
//     {
//         dup2(exec->fd[0], 0);
//         if (*(cmd + 1) != NULL)
//             dup2(p[1], 1);
//         close(p[0]);
//         execvp((*cmd)[0], *cmd);
//     }
//     else
//     {
//         wait(NULL);
//         close(p[1]);
//         exec->fd[0] = p[0];
//     }
// }