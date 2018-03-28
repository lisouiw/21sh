#include "../twenty.h"

void	sig_int(int sig)
{
    int status = 0;
    
    while (ed->rpz[0] == 0)
        ed = ed->next;
    if (ed->rpz[0] == 1 && ed->rpz[1] != 1)
        return;
    printf("INT[%i]\n", sig);
    // set_up_term();
    waitpid(-1, &status, 0);
    // printf("child exited witho = %d | %d\n",WIFSIGNALED(status), WEXITSTATUS(status));
    if(WIFSIGNALED(status) && WEXITSTATUS(status) == 0)
        write(1, "\n", 1);
    else
        exit(0);
}

void	sig_int3(int sig)
{
    ls_signal(0);       // pour ravoir le ctrl D
    fz->mode[3] = 0;
    printf("INT[%i]333333\n", sig);
    sig = 0;
    add_his(&hs, NULL, fz); //ajout historique
    write(1, "\n", 1);
    init_for_new(&hs, &fz, &ed);    
}
void	sig_quite(int sig)
{
    printf("QUITE %i\n", sig);
    exit(0);
}

void	sig_child(int sig)
{
    ls_signal(0);       // pour ravoir le ctrl D
    int status = 0;
    printf("INT[%i]\n", sig);
    // printf("AIDEZ MOI\n");
    wait(&status);
    printf("SIG_Child exited witha = %d |%d | %d| %d|\n", WIFEXITED(status), WEXITSTATUS(status),WIFSIGNALED(status), WTERMSIG(status) );
    // if (WTERMSIG(status) == 2)
    //     kill(0, SIGCONT);
    if (WTERMSIG(status) == 13)
        write(1, "\n", 1);
    // printf("child exited witha = %d |%d | %d| %d| %d| \n", WTERMSIG(status) , WCOREDUMP(status),WIFSTOPPED(status), WSTOPSIG(status), WIFCONTINUED(status));
}

void	ls_signal(int i)
{
    // printf("SINAL[%i]\n", i);
//     signal(SIGSTOP,sig_quite);
// signal(SIGTSTP, sig_quite);
 
    if (i != 0)
    {
        signal(SIGINT, sig_int3);
        signal(SIGCHLD, SIG_DFL);
    }
    else 
    {
        signal(SIGINT, sig_int);
        signal(SIGCHLD, SIG_DFL);
    }
	// signal(SIGQUIT,sig_quite);
    // signal(SIGKILL,sig_quite);
}


    // signal(SIGPIPE, sig_quite);
    // signal(SIGILL, sig_quite);
	// signal(SIGQUIT,sig_quite);
	// signal(SIGTSTP, sig_quite);
	// signal(SIGCONT, sig_quite);
    // signal(SIGQUIT,sig_quite);
	// signal(SIGABRT,sig_quite);
	// signal(SIGKILL,sig_quite);
	// signal(SIGTERM,sig_quite);
	// signal(SIGUSR1,sig_quite);
	// signal(SIGUSR2,sig_quite);
    // signal(SIGSTOP,sig_quite);
	// signal(SIGTTIN	,sig_quite);
	// signal(SIGTTOU,sig_quite);
    // signal(SIGCONT,sig_quite);
    // signal(SIGCHLD, sig_child);
	// signal(SIGCHLD, SIG_DFL);


// void	sig_child(int sig)
// {
//     // pid_t   p;
//     sig = 0;
// 	// signal(SIGCHLD, sig_child);
//     // printf("SIG_CHILD[%i][%i]\n", sig, waitpid(0, NULL, WNOHANG));
    
//     // while(wait(NULL) > 0);
//     // signal(SIGCHLD, sig_child);
//     // while ((p=waitpid(-1, NULL, WNOHANG | WUNTRACED)) == -1)
//     // {
//         // printf("==%i==\n", p);
//     // }
//     //     // if (p == 0)
//     //         // return;
//     // 	// signal(SIGCHLD, sig_child);
//     // }
//     // write(1, "\r", 1);
//     // exit(0);
//     // kill((p - 1), SIGKILL);
    
//     // signal(SIGCHLD, sig_child);
//     // printf("CHILD[%i][%i]\n", sig, waitpid(-1, NULL, WNOHANG));
    
//     // signal(SIGCHLD, sig_child);
    
//     // printf("======= CHILD [%i]===pid[%i]===\n", sig, (i = wait(NULL)));
//     //     printf("%i\n", i);
// //     kill(i -1 , SIGKILL);
// //     waitpid(-1, NULL, WNOHANG);
// }