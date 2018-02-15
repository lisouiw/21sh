//=======================GIVE_TAB=================================


// char    **give_tab(char **ar, t_cmd **ex)
// {
//     int     i;
//     int     e;
//     t_cmd   *tmp;
    
//     i = 0;
//     e = -1;
//     tmp = *ex;
//     while (tmp->next != NULL && tmp->type == 0)
//     {
//         ++i;
//         tmp = tmp->next;
//     }
//     if (tmp->type == 0)
//         ++i;
//     if (!(ar = (char**)malloc((i + 1) * sizeof(char*))))
//         return (NULL);
//     while (--i > -1)
//     {
//         ar[++e] = ft_strdup((*ex)->cmd);
//         *ex = (*ex)->next;
//     }
//     ar[i] = NULL;
//     return (ar);
// }

//===========================PIPE_FCT===============================


// t_env   *pipe_fct(t_exec *s, t_cmd *ex, t_env *env, pid_t pid)
// {
//     char       **arr;
//     int		new;
    
//     if (wait(0) && pid == 0)
//     {
//         dup2(s->fd_in, 0); //change the input according to the old one
//         if (ex->next->type != 42 && ex->next->type == 3 )
//             dup2(s->p[1], 1);
//         close(s->p[0]);
//         if (ex->next->type == 8)
//         {
//                 arr = ft_strsplit(ex->cmd, ' ');
//             	new = open(ex->next->cmd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//                 dup2(new, 1);
//                 close(s->p[1]);
//             	execvp(arr[0], arr);
//             	close(new);
//         }
//         else
//             env = exec_fct((arr = ft_strsplit(ex->cmd, ' ')), env);
//     }
//     else
//     {
//         ex = ex->next;
//         close(s->p[1]);
//         s->fd_in = s->p[0]; //save the input for the next command
//         s->fd_out = s->p[1];
//         printf("========GO===OUT===%s==%i=%i\n", ex->cmd, s->p[0], s->p[1]);
//     }
//     return (env);
// }

// ==========================LAUNCHCMD===========================

// t_env   *launchcmd(t_cmd *ex, t_env *env)
// {
//     t_exec     s;
//     pid_t      pid;
//     int        i;
//     char       **arr;

//     i = 0;
//     s.fd_in = 0;
//     while (ex->prev != NULL)
//         ex = ex->prev;
//     if (ex->type == 42 && ex->next->next->type == 42)   // condition si il ny qu'une commande
//     {           
//         if ((pid = fork()) == -1)
//             exit(EXIT_FAILURE);
//         if (pid == 0)
//             env = exec_fct((arr = ft_strsplit(ex->next->cmd, ' ')), env);
//         else
//             return (env);
//     }
//     while (ex->next != NULL && ++i < 10)
//     {
//         if (ex->type == 0)
//         {
//             pipe(s.p);
//             printf("========GO====%s=====\n", ex->cmd);
//             if ((pid = fork()) == -1)
//                 exit(EXIT_FAILURE);
//             env = pipe_fct(&s, ex, env, pid);
//         }
//         if (ex->next != NULL)
//             ex = ex->next;
//     }
  
//     return (env);
// }

//==================PIPE===========================================

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
