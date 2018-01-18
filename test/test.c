#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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
// 			}  
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
// 	pid_t pid;
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
// 			}  
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
//   char *rm[] = {"rm","such", NULL};
//   char *cat[] = {"cat", "-e", NULL};  
//   char **cmd[] = {rm , cat, NULL};

//   loop_pipe(cmd);
//   return (0);
// }


void    loop_pipe(char ***cmd) //ls | cat | wc -c > fifi"
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0;
	int		new;

	new = open("fifi", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (*cmd != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0); //change the input according to the old one 
			if (*(cmd + 1) != NULL)
			{
				// printf("coco %i && p[0] = %i & p[1] = %i\n", fd_in, p[0], p[1]);			
				dup2(p[1], 1);
			}  
			else 
				dup2(new, 1);
			
		   close(p[0]);
          	execvp((*cmd)[0], *cmd);
          	exit(EXIT_FAILURE);
        }
     	else
        {
			wait(NULL);
			close(p[1]);
			// printf("coucou %i %i\n", p[0], p[1]);
			
			fd_in = p[0]; //save the input for the next command
			cmd++;
        }
    }
}

int main()
{
  char *ls[] = {"ls", NULL};
  char *grep[] = {"grep", "pipe", NULL};
  char *wc[] = {"wc", "-c", NULL};
  char *cat[] = {"cat", NULL};  
  char **cmd[] = {ls, cat, wc, NULL};

  loop_pipe(cmd);
  return (0);
}