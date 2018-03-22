#include "../twenty.h"


int     parsing_dup_out(char *s, int n, t_cmd *ex)
{
    size_t     len;
    int         fd;
    if (ex)
        ;
    // printf("%i == %i\n", ft_atoi(s), n);
    if ((len = isnumber_len(s)) + 1 == ft_strlen(s) && s[len] == '-')
    {
        s[len] = '\0';
        // printf("====%i====\n", isatty(2));
        dup2(2, n);
        // redirection_check_create(ex->next);    
        close(2);
    }
    else
    {
        fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(dup(fd), n);
    }
    return(1);
}

int     parsing_dup_in(char *s, int n, t_cmd *ex)
{
    size_t     len;
    
    if (ex)
    ;
    if ((len = isnumber_len(s)) + 1 == ft_strlen(s) && s[len] == '-')
    {
        s[len] = '\0';
        dup2(n, (len = ft_atoi(s)));
        // redirection_check_create(ex->next);        
        close(len);
    }
    else
    {
        len = open(s, O_RDONLY);
        dup2(n, len);
    }
    return(1);
}



int     redirection_check_create(t_cmd *ex)    //
{
    char    **spl = NULL;

    while ((ex)->type == 6 || (ex)->type == 7 || (ex)->type == 8 || (ex)->type == 9 || (ex)->type == 10 || (ex)->type == 11)
    {
        printf("%i\n", ex->type);
        if ((ex)->type == 8 || (ex)->type == 9) //creer les fichier
            redirection_file_create(ex);
        else if ((ex)->type == 7 && redirection_file_check(ex) == 0) //verif exist. Si non, exit.
                return (0);
        else if (ex->type == 10)
        {
            dup2(1, 2);
            // close(2);
            // aggregation_out(ft_strsplit(ex->cmd, ' '))
            // spl = ft_strsplit(ex->cmd, ' ');
            // if (spl[2] == '\0')
            //     isnumber(spl[1]) ? dup2(ft_atoi(spl[1]), 1) : parsing_dup_out(spl[1], 1, ex);
            // else
            //     isnumber(spl[2]) ? dup2(ft_atoi(spl[2]), ft_atoi(spl[0])) : parsing_dup_out(spl[2], ft_atoi(spl[0]), ex);
            // dup2(1,2);
            // // dup2(isnumber(spl[2]) ? ft_atoi(spl[2]) : parsing_dup_(spl[2]), ft_atoi(spl[0]));
            // free_tab(spl);
        }
        else if (ex->type == 11)
        {
            spl = ft_strsplit(ex->cmd, ' ');
            if (spl[2] == '\0')
                isnumber(spl[1]) ? dup2(0, ft_atoi(spl[1])) : parsing_dup_in(spl[1], 0, ex);
            else
                isnumber(spl[2]) ? dup2(ft_atoi(spl[0]), ft_atoi(spl[2])) : parsing_dup_in(spl[2], ft_atoi(spl[0]), ex);
            free_tab(spl);
        }
        // else if (ex->type == 6)
        //     printf("HOLA\n");
        ex = (ex)->next;
    }
    return (1);
}

void    redirection_file_create(t_cmd *ex)
{
    int     nw;
    char    **arr;
      
    arr = ft_strsplit((ex)->cmd, ' ');
    if ((ex)->type == 8)
        nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else
        nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_APPEND, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_APPEND, 0644);
    dup2(nw, (arr[2] == NULL ? 1 : ft_atoi(arr[0])));
    free_tab(arr);
    close(nw);
}

int     redirection_file_check(t_cmd *ex)
{
    int     nw;
    char    **arr;

    arr = ft_strsplit((ex)->cmd, ' ');
    nw = (arr[2] == NULL) ? open(arr[1], O_RDONLY) : open(arr[2], O_RDONLY);
    if (nw == -1)
    {
        ft_putstr_fd("sh: ", 2);
        ft_putstr_fd(((arr[2] == NULL) ? arr[1] : arr[2]), 2);         ////Problem a fix
        ft_putstr_fd(": No such file or directory\n", 2);
        free_tab(arr);
        return (0);
    }
    close(nw);
    free_tab(arr);
    return (1);
}






























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



// void    redirecting_in(t_cmd **ex, t_env **env, int nw)
// {
//     pid_t       pid;
//     char        **arr;
//     int         i = 0;

//     arr = NULL;  
//     if ((pid = fork()) == -1)
//         exit(EXIT_FAILURE);
//     else if (pid == 0)
//     {
//         nw = redirection_file_check(&arr, *ex, nw);
//         i = dup(0);
//         dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(arr[0])));
//         close(nw);
//         free_tab(arr);
//         arr = ft_strsplit((*ex)->prev->cmd, ' ');
//         *env = exec_fct_nf(arr, *env);
//     }
//     else
//     {
//         kill(wait(NULL), SIGKILL);
//         free_tab(arr);
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
//         arr = ft_strsplit((*ex)->cmd, ' ');
//         nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
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

// int     parsing_dup_out(char *s, int n)
// {
//     size_t     len;
    
//     // printf("===LEN=%zu===lenOFs=%zu====c[%c]===ISATTY[%i][%i][%i][%i]===\n", len, ft_strlen(s), s[len], isatty(99), isatty(1), isatty(2), isatty(3));
//     // len = isnumber_len(s);
//     if ((len = isnumber_len(s)) + 1 == ft_strlen(s) && s[len] == '-')
//     {
//         s[len] = '\0';
//         dup2((len = ft_atoi(s)), n);
//         close(len);
//     }
//     else
//     {
//         len = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         dup2(len, n);
//     }
//     return(1);
// }