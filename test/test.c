#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

// void	pii(char **argv)
// {
// 	char	*cmd1;
// 	char	*argv1[3];
// 	char	*argv2[3];
// 	int		fd[2];
// 	pid_t	fils = -1;
	
// 	cmd1 = "/bin/ls";
// 	argv1[0] = cmd1;
// 	argv1[1] = "-lF";
// 	argv1[2] = NULL;
// 	argv2[0] = "/bin/cat";
// 	argv2[1] = "-e";
// 	argv2[2] = NULL;
// 	pipe(fd);
	
// 	fils = fork();
	
// 	if (fils != 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		execve(cmd1, argv1, NULL);
// 		exit(0);
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[1]);
// 	execve(argv2[0], argv2, NULL);
	
// }

// int		 main(int ac, char **argv)
// {
// 	pid_t	fils;
// 	int		fd[2];

// 	fils = fork();
	

// 	if (fils == -1)
// 	{
// 		fprintf(stderr, "Erreur de création du processus.\n");
// 		return 1;
// 	}
	
// 	if (fils != 0)
// 	{
// 			pii(argv);
// 	}
	
// 	wait(NULL);
// 	return 0;
// }




// void    loop_pipe(char ***cmd) 
// {
// 	int   p[2];
// 	pid_t pid;
// 	int   fd_in = 0;

// 	while (*cmd != NULL)
// 	{
// 		pipe(p);
// 		if ((pid = fork()) == -1)
// 			exit(EXIT_FAILURE);
// 		else if (pid == 0)
// 		{
// 			dup2(fd_in, 0); //change the input according to the old one 
// 			if (*(cmd + 1) != NULL)
// 			{
// 				printf("coco %i && p[0] = %i & p[1] = %i\n", fd_in, p[0], p[1]);			
// 				dup2(p[1], 1);
// 		   close(p[0]);
//           	execvp((*cmd)[0], *cmd);
//           	exit(EXIT_FAILURE);
//         }
//      	else
//         {
// 			wait(NULL);
// 			close(p[1]);
// 			printf("coucou %i %i\n", p[0], p[1]);
			
// 			fd_in = p[0]; //save the input for the next command
// 			cmd++;
//         }
//     }
// }

// int main()
// {
//   char *ls[] = {"ls", NULL};
//   char *grep[] = {"grep", "pipe", NULL};
//   char *wc[] = {"wc", NULL};
//   char **cmd[] = {ls, grep, wc, NULL};

//   loop_pipe(cmd);
//   return (0);
// }

// void    loop_pipe(char ***cmd) //- Lancez la commande "echo "No dollar character" 1>&2 | cat -e". La sortie doit être "No dollar character".
// {
// 	int   p[2];
// 	int   fd_in = 0;

// 	while (*cmd != NULL)
// 	{
// 		pipe(p);
// 		if ((pid = fork()) == -1)
// 			exit(EXIT_FAILURE);
// 		else if (pid == 0)
// 		{
// 			if (**cmd[0] == 'e')
// 			{
// 				// printf("--%c\n",**cmd[0]);
// 				dup2(2, 1); //change the input according to the old one 
// 				close(p[1]);
// 			}
// 			dup2(fd_in, 0); //change the input according to the old one 			
// 			if (*(cmd + 1) != NULL)
// 			{
// 				// printf("coco %i && p[0] = %i & p[1] = %i\n", fd_in, p[0], p[1]);			
// 				dup2(p[1], 1);
// 			}  
// 		   close(p[0]);
//           	execvp((*cmd)[0], *cmd);
//           	exit(EXIT_FAILURE);
//         }
//      	else
//         {
// 			wait(NULL);
// 			close(p[1]);
// 			// printf("coucou %i %i\n", p[0], p[1]);
			
// 			fd_in = p[0]; //save the input for the next command
// 			cmd++;
//         }
//     }
// }

// int main()
// {
//   char *ls[] = {"ls","dosjdskl",  NULL};
//   char *grep[] = {"grep", "pipe", NULL};
//   char *wc[] = {"wc", NULL};
//   char *cat[] = {"cat", "-e", NULL};
//   char *echo[] = {"echo", "No dollar character", NULL};
  
// //   char **cmd[] = {ls, grep, wc, NULL};
// char **cmd[] = {echo, cat , NULL};


//   loop_pipe(cmd);
//   return (0);
// }


// void    loop_pipe(char ***cmd) //rm nosuchfile 2>&1 | cat -e" | La sortie doit être :"rm: nosuchfile: No such file or directory$"
// {
// 	int   p[2];
// 	pid_t pid;
// 	int   fd_in = 0;

// 	while (*cmd != NULL)
// 	{
// 		pipe(p);
// 		if ((pid = fork()) == -1)
// 			exit(EXIT_FAILURE);
// 		else if (pid == 0)
// 		{
// 			if (**cmd[0] == 'r')
// 			{
// 				dup2(2, 1);
// 				dup2(p[1], 2);				
// 			}
// 			dup2(fd_in, 0); //change the input according to the old one 
// 			if (*(cmd + 1) != NULL)
// 			{
// 				printf("coco %i && p[0] = %i & p[1] = %i\n", fd_in, p[0], p[1]);			
// 				dup2(p[1], 1);
// 		        close(p[0]);
//              execvp((*cmd)[0], *cmd);
//          }
//      	else
//          {
// 			    wait(NULL);
// 			    close(p[1]);
// 			    printf("coucou %i %i\n", p[0], p[1]);
//   			fd_in = p[0]; //save the input for the next command
// 	    		cmd++;
//          }
//      }
//  }

// int main()
// {
//   char *ls[] = {"ls", NULL};
//   char *grep[] = {"grep", "pipe", NULL};
//   char *wc[] = {"wc", NULL};
//   char *rm[] = {"rm","such", NULL};
//   char *cat[] = {"cat", "-e", NULL};  
//   char **cmd[] = {rm , cat, NULL};

//   loop_pipe(cmd);
//   return (0);
// }


// void    loop_pipe(char ***cmd) //ls | cat | wc -c > fifi"
// {
// 	int		p[2];
// 	pid_t	pid;
// 	int		fd_in = 0;
// 	int		new;

// 	new = open("fifi", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	while (*cmd != NULL)
// 	{
// 		pipe(p);
// 		if ((pid = fork()) == -1)
// 			exit(EXIT_FAILURE);
// 		else if (pid == 0)
// 		{
// 			dup2(fd_in, 0); //change the input according to the old one 
// 			if (*(cmd + 1) != NULL)
// 			{
// 				// printf("coco %i && p[0] = %i & p[1] = %i\n", fd_in, p[0], p[1]);			
// 				dup2(p[1], 1);
// 			}  
// 			else 
// 				dup2(new, 1);
			
// 		   close(p[0]);
//           	execvp((*cmd)[0], *cmd);
//           	exit(EXIT_FAILURE);
//         }
//      	else
//         {
// 			wait(NULL);
// 			close(p[1]);
// 			// printf("coucou %i %i\n", p[0], p[1]);
			
// 			fd_in = p[0]; //save the input for the next command
// 			cmd++;
//         }
//     }
// }

// int main()
// {
//   char *ls[] = {"ls", NULL};
//   char *grep[] = {"grep", "pipe", NULL};
//   char *wc[] = {"wc", "-c", NULL};
//   char *cat[] = {"cat", NULL};  
//   char **cmd[] = {ls, cat, wc, NULL};

//   loop_pipe(cmd);
//   return (0);
// }


/////////////////////// Redirection d'Entree //////////////////////

// void    loop_pipe(char ***cmd) //ls 3< "."
// {
// 	int		p[2];
// 	DIR		*op;
// 	int		fd_in = 0;
// 	int		new;
// 	int		o;
	
// 	pipe(p);
// 	op = opendir(*cmd[1]);
// 	if (op == NULL  && (o = open(*cmd[1], O_RDONLY)) == -1 )
// 	{
// 		printf("sh: %s: No such file or directory\n", *cmd[1]);
// 		return;
// 	}
// 	dup2(o, 0);
// 	dup2(p[0], o);
// 	close(p[1]);
// 	// printf("%s\n", (*cmd)[1]);
// 	execvp((*cmd)[0], *cmd);
// 	close(o);
// 	closedir(op);
// }

// int main()
// {
// 	char *ls[] = {"ls", "l","-a", NULL};	
// 	char *wc[] = {"wc", "-c", NULL};
// 	char *cat[] = {"cat", NULL};  
// 	char *redic[] = {"../../../../tmp/test.txt", NULL};  
// 	char *redic2[] = {".", NULL};  
// 	// char **cmd[] = {wc, redic, NULL};
// 	char **cmd[] = {ls, redic2, NULL};
	

// 	loop_pipe(cmd);
// 	return (0);
// }

//////////////////////// Redirection de Sortie//////////////////////////////////////

// void    loop_pipe(char ***cmd) 
// {
// 	int  	 p[2];
// 	pid_t	pid;
// 	int		fd_in = 0;
// 	int		new;

// 	new = open(*cmd[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	printf("%i\n", new);

// 	dup2(new, 1);
// 	execvp((*cmd)[0], *cmd);
// 	close(new);
// }

// int main()
// {
// 	char *cat[] = {"cat", "-e" , "1", NULL};
//  	char *ls[] = {"ls", NULL};
//   	char *grep[] = {"grep", "pipe", NULL};
// 	char *wc[] = {"wc", NULL};
// 	char *word[] = {"papa", NULL};
//   	char **cmd[] = {cat, word, NULL};

//   loop_pipe(cmd);
//   return (0);
// }

//////////////////////// Ajout Redirection de Sortie//////////////////////////////////////

// void    loop_pipe(char ***cmd) 
// {
// 	int  	 p[2];
// 	pid_t	pid;
// 	int		fd_in = 0;
// 	int		new;

// 	new = open(*cmd[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	printf("%i\n", new);

// 	dup2(new, 1);
// 	execvp((*cmd)[0], *cmd);
// 	close(new);
// }

// int main()
// {
// 	char *cat[] = {"cat", "-e" , "1ss", NULL};
//  	char *ls[] = {"ls", NULL};
//   	char *grep[] = {"grep", "pipe", NULL};
// 	char *wc[] = {"wc", NULL};
// 	char *word[] = {"papa", NULL};
//   	char **cmd[] = {cat, word, NULL};

//   loop_pipe(cmd);
//   return (0);
// }


// /////////////////////// Redirection d'Entree //////////////////////

// void    loop_pipe(char ***cmd) //ls 3< "."
// {
// 	int		p[2];
// 	DIR		*op;
// 	int		fd_in = 0;
// 	int		new;
// 	int		o;
// 		pid_t	pid;
// 	char 	buf[1000];
// 	int		i;

// 		if ((o = open(*cmd[1], O_RDONLY)) == -1 )
// 		{
// 			printf("sh: %s: No such file or directory\n", *cmd[1]);
// 			return;
// 		}
// 		dup2(o, 0);
// 		if ( pid == 0 && wait(0) && (execvp("cat", cmd[0])) == -1)
// 			printf("no o\n");

// 		close(o);
// }

// int main(void)
// {
// 	char *ls[] = {"ls", NULL};	
// 	char *wc[] = {"wc", "-c", NULL};
// 	char *cat[] = {"cat", NULL};  
// 	char *redic[] = {"../../../../tmp/test.txt", NULL};  
// 	char *redic2[] = {"1", NULL};  
// 	// char **cmd[] = {wc, redic, NULL};
// 	char **cmd[] = {cat, redic2, NULL};
	

// 	loop_pipe(cmd);
// 	loop_pipe(cmd);
	
// 	return (0);
// }

/////////////////////// Redirection Pipe //////////////////////

// void    loop_pipe(char ***cmd) //ls 3< "."
// {
//     int		p[2];
// 	pid_t   pid;
// 	int		fd_in = 0;
    
//     while (*cmd != NULL)
//     {
//         pipe(p);
//         if ((pid = fork()) == -1)
//             exit(EXIT_FAILURE);
//         else if (pid == 0)
//         {
//             dup2(fd_in, 0);
//             if (*(cmd + 1) != NULL)
//                 dup2(p[1], 1);
//             close(p[0]);
//             execvp((*cmd)[0], *cmd);
//         }
//         else
//         {
//             wait(NULL);
//             close(p[1]);
//             fd_in = p[0];
//             ++cmd;
//         }
//     }
// }

// int main()
// {
// 	char *ls[] = {"ls", "-l", NULL};	
// 	char *wc[] = {"wc", "-c", NULL};
// 	char *cat[] = {"cat", NULL};  
// 	char *redic[] = {"../../../../tmp/test.txt", NULL};  
// 	char *redic2[] = {"grep", "Jan", NULL};  
// 	// char **cmd[] = {wc, redic, NULL};
// 	char **cmd[] = {ls, redic2,wc, NULL};

// 	loop_pipe(cmd);
// 	return (0);
// }

///////////////////// Redirection Pipe //////////////////////

void    loop_pipe(char ***cmd) //ls 3< "."
{
    int		p[2];
	pid_t   pid;
    int		fd_in = 0;
    char    BUF[100];
    int     i;
    while (*cmd != NULL)
    {
        pipe(p);
        if ((pid = fork()) == -1)
            exit(EXIT_FAILURE);
        else if (pid == 0)
        {
			printf("===ENTREE==%i==fd_in = %i & p[0] = %i && p[1] = %i\n", pid, fd_in, p[0], p[1]);
            dup2(fd_in, 0);
            if (*(cmd + 1) != NULL)
                dup2(p[1], 1);
            printf("===NO=DUP==%i==fd_in = %i & p[0] = %i && p[1] = %i\n", pid, fd_in, p[0], p[1]);
            close(p[0]);
            execvp((*cmd)[0], *cmd);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            fd_in = p[0];
			printf("===SORTIE=%i==fd_in = %i & p[0] = %i && p[1] = %i\n\n", pid, fd_in, p[0], p[1]);
            ++cmd;
        }
    }
}

int main()
{
	char *ls[] = {"ls", "-l", NULL};	
	char *wc[] = {"wc", "-c", NULL};
	char *cat[] = {"cat", NULL};  
	char *redic[] = {"../../../../tmp/test.txt", NULL};  
	char *redic2[] = {"grep", "Jan", NULL};  
	// char **cmd[] = {wc, redic, NULL};
	char **cmd[] = {ls, redic2,wc, NULL};

	loop_pipe(cmd);
	return (0);
}
