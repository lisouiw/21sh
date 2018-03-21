#include "../twenty.h"
#include <unistd.h>

int   p;

void    sign(int a)
{
    exit(0);
}


int     main()
{
    char    *ls_args[] = {"ls", NULL};
    char    *buf;
    char    *init = NULL;
    int     i = 0;
    int     pid;
    int     p[2];
    int fd;
    int z;

    z = dup(0);
    fd = dup(0);
        // close(0);
        
    while (2)
    {
        // if ((fd = open(NULL, O_RDONLY)) == -1)
        //     exit(0);
        // dup2(p[0], fd);
        get_next_line(z, &buf);
        if (strcmp("lo", buf) == 0)
        {
            pid = fork();
            if (pid == 0)
            {

                write(0, init, ft_strlen(init));
                execvp("ls", ls_args);
                exit(0);
            }
            else
            {
                wait(NULL);
                // exit(0);
               return(0);
            }
         
        }
        else
        {
            if (init == NULL)
                init = ft_strdup(buf);
            else
            init = ft_strjoin(init,ft_strjoin("\n", buf));
        }
        // else
        // {
        //     write(0, buf, ft_strlen(buf));
        //     write(0, "\n", 1);
        // }
    }
}


// void  loop_pipe(char ***cmd)           
// {
//   int   p[2];
//   pid_t pid;
//   int   fd_in = 0;

//   while (*cmd != NULL)
//     {
//       pipe(p);
//       if ((pid = fork()) == -1)
//         {
//           exit(EXIT_FAILURE);
//         }
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
