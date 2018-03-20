#include "../twenty.h"

///////////////////////////ls -z  > co 2>&1/////////////////////////////

int     main()
{
    int     out;
    int     fd;
    // char    *cmd[] = {"ls", "-z", NULL};
    char    *cmd[] = {"ls", NULL};

    out = dup(1);
    fd = open("co" , O_CREAT | O_RDWR | O_TRUNC, 0644); 
    dup2(fd,1);
    dup2(1, 2);
    execvp(cmd[0], cmd);
    
}


/////////////////////////////ls -z 2>&1 > co /////////////////////////////////

// int     main()
// {
//     int     out;
//     int     fd;
//     char    *cmd[] = {"ls", "-z", NULL};
//     // char    *cmd[] = {"ls", NULL};

//     out = dup(1);
//     fd = open("co" , O_CREAT | O_RDWR | O_TRUNC, 0644); 
//     dup2(1, 2);
//     dup2(fd,1);
//     execvp(cmd[0], cmd);
    
// }