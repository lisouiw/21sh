#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int     main()
{
    int fd;

    if((fd = open("co", O_RDONLY )) == -1)
        printf("ERROR\n");
    else
        dup2(0, fd);
    
        // dup2(fd, 0);

    return (0);
}