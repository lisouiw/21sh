#include "../twenty.h"

int 	main(void)
{
	pid_t	fils;
	char	*cut[] = {"ls", NULL};

	if ((fils = fork()) == -1)
		exit(1);
    if (wait(0) && fils == 0)
	   if(execve("/bin/ls", cut, NULL) == -1)
        	puts("sh: command not found: ");
    return (1);
}