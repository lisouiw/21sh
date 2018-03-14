#include "../twenty.h"

int   p;

void    sign(int a)
{
    exit(0);
}


int     main()
{
    char *ls_args[] = {"ls", NULL};
    char    *buf;
    int     i = 1;
    size_t  len = 0;
    int     p[2];
    int fd;
    int r;
    
    int pid;

    signal(SIGINT, sign);
    fd = open("/tmp/a", O_CREAT , 0644);
    fd = open("/tmp/a", O_RDWR| O_APPEND);
    while (i)
    {
        i = get_next_line(0, &buf);
        buf[ft_strlen(buf)] = '\0';

        // i = read(3, &bf, 100);
        if (strcmp("lo", buf) == 0)
        {
            pid = fork();
            if (pid == 0)
            {
                close(fd);
                fd = open("/tmp/a", O_RDONLY);
                dup2(fd, 0);
                printf("==========CHILD==========\n");
                r = execvp("cat", ls_args);
                exit(0);
            }
            else
            {
                wait(0);
               close(fd);
               return(0);
            }
        }
        else
        {
            write(fd, buf, ft_strlen(buf));
            write(fd, "\n", 1);
        }
    }
}