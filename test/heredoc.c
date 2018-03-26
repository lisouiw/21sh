#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

int pid;
int r;
int status;

int main()
{
        char *ls_args[] = {"ls", NULL};
        char *grep_args[] = {"grep", "a", NULL};
        int fd;
int   p[2];

         pid = fork();
         if (pid  != 0)
        {
            // Parent: Output is to child via pipe[1]
            // Change stdout to pipe[1]
         // dup2(0, fd);
            // dup2(fd, 0);
            // fd = open("/tmp/in", O_CREAT & O_RDWR & O_TRUNC, 0644);
            write(0, "pute\n", 5);

            // dup2( 0,fd);
            wait(0);
            dup2(fd, 0);
            r = execvp("cat", ls_args);
            exit(0);
        }
        else
        {
            wait(&status);
             printf("%i | %i | %i | %i | %i | %i | %i| %i\n",WIFEXITED(status),WEXITSTATUS(status),WIFSIGNALED(status),WTERMSIG(status),WCOREDUMP(status),WIFSTOPPED(status),WSTOPSIG(status),WIFCONTINUED(status));
            // dup2(r, 0);
            // dup2(p, 1);
                // kill(wait(NULL), 0);
        }
    return r;
}