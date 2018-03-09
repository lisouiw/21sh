#include "../twenty.h"

void    redirection_f(t_cmd **ex, t_env **env, t_exec *s)
{
    char    **arr;
    pid_t       pid;
    

    if (s || env)
        ;
    arr = ft_strsplit((*ex)->cmd, ' ');
    *ex = (*ex)->next;
    
    if ((pid = fork()) == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
    {
        if (redirection_check_create(*ex))
            redirecting_in(ex, env, arr);
        else
            exit(0);
    }
    free_tab(arr);
}

char    **give_seven(t_cmd *ex)
{
    while (ex->next->type == 8 || ex->next->type == 7 || ex->next->type == 9)
        ex = ex->next;
    while (ex->type == 8 || ex->type == 9)
        ex = ex->prev;
    if (ex->type != 7)
        return (NULL);
    return (ft_strsplit(ex->cmd, ' '));
}

void    redirecting_in(t_cmd **ex, t_env **env, char **arr)
{
    int         nw;
    char        **tmp;
    
    if ((tmp = give_seven(*ex)) != NULL)
    {
        nw = (tmp[2] == NULL) ? open(tmp[1], O_RDONLY) : open(tmp[2], O_RDONLY);
        // dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(tmp[0])));
        dup2((arr[2] == NULL ? 0 : ft_atoi(tmp[0])), nw);
        
    }
    wait(0);
    *env = exec_fct_nf(arr, *env);
}

// void    redirecting_in(t_cmd **ex, t_env **env, char **arr)
// {
//     pid_t       pid;
//     // int         i;
//     // int         a;
    
//     if (*ex)
//         ;
//         printf("========\n");
//     if ((pid = fork()) == -1)
//         exit(EXIT_FAILURE);
//     else if (pid == 0)
//     {
//         printf("========\n");
//         // exit(0);
//         // i = open("i", O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         // a = open("a", O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         // dup2(i, 1) ;
//         // dup2(a, 1 );
//         // arr = ft_strsplit((ex)->cmd, ' ');
//         // nw = (arr[2] == NULL) ? open(arr[1], O_RDONLY) : open(arr[2], O_RDONLY);
//         // dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(arr[0])));
//         // free_tab(arr);
//         *env = exec_fct_nf(arr, *env);
//     }
//     else
//     {
//         kill(wait(NULL), SIGKILL);
//         // free_tab(arr);
//     }
// }

// void    redirecting_out(t_cmd **ex, t_env **env, int nw)
// {
//     pid_t       pid;
//     char       **arr;
//     char       **last;    
 
//     last = NULL;
//     if ((pid = fork()) == -1)
//         exit(EXIT_FAILURE);
//     else if (pid == 0)
//     {
//         arr = ft_strsplit((*ex)->prev->cmd, ' ');
//         nw = redirection_file_create(&(*ex), &(*last));
//         dup2(nw, 1);
//         close(nw);
//         *env = exec_fct_nf(arr, *env);
//     }
// }





// int     redirection_file_check(char ***arr, t_cmd *ex, int nw)
// {
//     char    **pute;

//     *arr = ft_strsplit((ex)->cmd, ' ');
//     while (nw != -1 && (ex)->type == 7)
//     {
//         pute = ft_strsplit((ex)->cmd, ' ');
//         nw = (pute[2] == NULL) ? open(pute[1], O_RDONLY) : open(pute[2], O_RDONLY);
//         if ((ex)->next->type == 7)
//             close(nw);
//         free_tab(pute);
//         ex = (ex)->next;
//     }
//     if (nw == -1)
//     {
//         free_tab(*arr);
//         ft_putstr_fd("error\n", 2);
//         exit(0);
//     }   
//     return (nw);
// }


// int    redirection_file_create(t_cmd **ex, char **arr)
// {
//     int     nw;
    
//     nw = 0;
//     while ((*ex)->type == 8)
//     {
//         nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         arr = ft_strsplit((*ex)->cmd, ' ');
//         if ((*ex)->next->type == 8)
//         {
//             free_tab(arr);
//             close(nw);
//         }
//         else
//             return (nw); 
//         *ex = (*ex)->next;
//     }
//     return (nw); 
// }

// void    redirecting_out(t_cmd **ex, t_env **env, int nw)
// {
//     char       **arr;
//     t_cmd       *tmp;
//     int         i = 0;
 

//     while ((*ex)->type == 7)
//         *ex = (*ex)->next;
//     while (nw != -1 && (ex)->type == 7)
//     {
//         pute = ft_strsplit((ex)->cmd, ' ');
//         nw = (pute[2] == NULL) ? open(pute[1], O_RDONLY) : open(pute[2], O_RDONLY);
//         if ((ex)->next->type == 7)
//             close(nw);
//         free_tab(pute);
//         ex = (ex)->next;
//     }
//     if ((pid = fork()) == -1)
//         exit(EXIT_FAILURE);
//     else if (pid == 0)
//     {
//         arr = ft_strsplit((*ex)->cmd, ' ');

//         nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         i = dup(1);
//         dup2(nw, (arr[2] == NULL ? 1 : ft_atoi(arr[0])));
//         tmp = *ex;
//         free_tab(arr);
//         while (tmp->prev->type != 0  && tmp->prev->type != 42)
//             tmp = tmp->prev;
//         if (wait(0) && tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')))
//         {
//            *env = exec_fct_nf(arr, *env);
//             free_tab(arr);
//         }
//     }
//     else
//     {
//         wait(0);
//         close(nw);
//         dup2(1, i);
//     }
// }