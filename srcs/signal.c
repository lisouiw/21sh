#include "../twenty.h"

void	ls_signal(void)
{
    signal(SIGILL, sig_quite);
	signal(SIGQUIT,sig_quite);
    signal(SIGPIPE, sig_pipe);
    signal(SIGINT, sig_int);
	signal(SIGTSTP, sig_quite);
	signal(SIGCONT, sig_quite);
    signal(SIGQUIT,sig_quite);
	signal(SIGABRT,sig_quite);
	signal(SIGKILL,sig_quite);
	signal(SIGTERM,sig_quite);
	// signal(SIGUSR1,sig_quite);
	// signal(SIGUSR2,sig_quite);
    signal(SIGSTOP,sig_quite);
	signal(SIGTTIN	,sig_quite);
	signal(SIGTTOU,sig_quite);
    signal(SIGCONT,sig_quite);
	// signal(SIGCHLD, sig_child);
}


void	sig_pipe(int sig)
{
    printf("PIPE %i\n", sig);
    exit(0);
}
void	sig_int(int sig)
{
    printf("INT %i\n", sig);
    exit(0);
}
void	sig_quite(int sig)
{
    printf("QUITE %i\n", sig);
    exit(0);
}

void	sig_child(int sig)
{
    pid_t   p;
    sig = 0;
    
    // while(wait(NULL) > 0);
    // signal(SIGCHLD, sig_child);
    while ((p=waitpid(-1, NULL, WNOHANG | WUNTRACED)) == -1)
    {
        printf("==%i==\n", p);
    }
    //     // if (p == 0)
    //         // return;
    // 	// signal(SIGCHLD, sig_child);
    // }
    // write(1, "\r", 1);
    // exit(0);
    // kill((p - 1), SIGKILL);
    
    // signal(SIGCHLD, sig_child);
    // printf("CHILD[%i][%i]\n", sig, waitpid(-1, NULL, WNOHANG));
    
    // signal(SIGCHLD, sig_child);
    
    // printf("======= CHILD [%i]===pid[%i]===\n", sig, (i = wait(NULL)));
    //     printf("%i\n", i);
//     kill(i -1 , SIGKILL);
//     waitpid(-1, NULL, WNOHANG);
}