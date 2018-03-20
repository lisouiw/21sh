#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

int main() 
{
    char *ls[] = {"ls","-l",  NULL};
  int link[2];
  pid_t pid;
//   char foo[4096];

pipe(link);
//   if (pipe(link)==-1)
    // die("pipe");

  if ((pid = fork()) == -1)
  ;
    // die("fork");
  if(pid == 0) {

    // dup2 (link[0], 0);
    // dup2 (link[1], 1);
    close(link[0]);
    // close(link[1]);
    execvp(ls[0], ls);
    // die("execl");
    exit(0);

  }
   else {

    wait(NULL);
    close(link[1]);
    // int nbytes = read(link[0], foo, sizeof(foo));
    // printf("Output: (%.*s)\n", nbytes, foo);

  }
  return 0;
}