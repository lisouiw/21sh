#include "../twenty.h"

int   p;

void    sign(int a)
{
    exit(0);
}


int     main()
{
    char    *ls_args[] = {"ls", NULL};
    char    *buf;
    int     i = 1;
    int     pid;
    int fd;
    int z;

    z = dup(0);
    signal(SIGINT, sign);
    while (i)
    {
        fd = open(NULL, O_RDONLY);
        i = get_next_line(0, &buf);
        if (strcmp("lo", buf) == 0)
        {
            pid = fork();
            if (pid == 0)
            {
                printf("==================\n");
                execvp("cat", ls_args);
                exit(0);
            }
            else
            {
                wait(0);
               return(0);
            }
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
