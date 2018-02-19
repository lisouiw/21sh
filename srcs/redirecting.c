#include "../twenty.h"

void    redirecting_out(t_cmd **ex, t_env **env, int nw)
{
    pid_t      pid;
    char       **arr;
    t_cmd       *tmp;
    int         i = 0;
 
    if ((pid = fork()) == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
    {
        arr = ft_strsplit((*ex)->cmd, ' ');
        nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        i = dup(1);
        dup2(nw, (arr[2] == NULL ? 1 : ft_atoi(arr[0])));
        tmp = *ex;
        free_tab(arr);
        while (tmp->prev->type != 0  && tmp->prev->type != 42)
            tmp = tmp->prev;
        if (wait(0) && tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')))
        {
           *env = exec_fct_nf(arr, *env);
            free_tab(arr);
        }
    }
    else
    {
        wait(0);
        close(nw);
        dup2(1, i);
    }
}

void    redirecting_in(t_cmd **ex, t_env **env, int nw)
{
    pid_t       pid;
    char        **arr = NULL;
    t_cmd       *tmp;
    int         i = 0;

    if ((*ex)->type == 7)
    {    
        if ((pid = fork()) == -1)
            exit(EXIT_FAILURE);
        else if (pid == 0)
        {
            arr = ft_strsplit((*ex)->cmd, ' ');
            nw = (arr[2] == NULL) ? open(arr[1], O_RDONLY) : open(arr[2], O_RDONLY);
            if (nw == -1)
            {
                printf("error\n");
                exit(0);
            }
            // else if ((*ex)->prev->type != 0)
            //     exit(0);
            i = dup(0);
            dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(arr[0])));
            close(nw);
            tmp = *ex;
            free_tab(arr);
            while (tmp->prev->type != 0  && tmp->prev->type != 42)
                tmp = tmp->prev;
            if (tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')) && wait(0))
                *env = exec_fct_nf(arr, *env);
        }
        else
        {
            wait(0);
            free_tab(arr);
            dup2(i, 0);
        }
    }
}

void    app_redirecting_out(t_cmd **ex, t_env **env, int nw)
{
    pid_t      pid;
    char       **arr;
    t_cmd       *tmp;
    int         i = 0;
 
    if ((pid = fork()) == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
    {
        arr = ft_strsplit((*ex)->cmd, ' ');
        nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_APPEND, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        i = dup(1);
        dup2(nw, (arr[2] == NULL ? 1 : ft_atoi(arr[0])));
        tmp = *ex;
        free_tab(arr);
        while (tmp->prev->type != 0  && tmp->prev->type != 42)
            tmp = tmp->prev;
        if (wait(0) && tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')))
        {
           *env = exec_fct_nf(arr, *env);
            free_tab(arr);
        }
    }
    else
    {
        wait(0);
        close(nw);
        dup2(1 ,i);
    }
}


void    redirecting_out_child(t_cmd **ex, t_env **env, int nw, pid_t *pid, t_exec *s)
{
    char       **arr;
    t_cmd       *tmp;
    int         i = 0;

    if (s->in)
    ;
    if (*pid == 0)
    {
        arr = ft_strsplit((*ex)->cmd, ' ');
        nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        i = dup(1);
        dup2(nw, (arr[2] == NULL ? s->out : ft_atoi(arr[0])));
        close(nw);
        tmp = *ex;
        free_tab(arr);
        while (tmp->prev->type != 0  && tmp->prev->type != 42)
            tmp = tmp->prev;
        if (tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')))
        {
            wait(0);
            *env = exec_fct_nf(arr, *env);
            free_tab(arr);
        }
    }
    // else 
    // {
    //     s->in = s->p[0];
    //     s->out = s->p[1];
    //     close (s->p[0]);
    //     close (s->p[1]);
    //     // dup2(i, 1);
    //     dup2(1 ,i);
    //     close(i);
    // }
}

void    redirecting_in_child(t_cmd **ex, t_env **env, int nw, pid_t *pid, t_exec *s)
{
    char        **arr = NULL;
    t_cmd       *tmp;

        if (s->in)
            ;
        printf("IN\n");
        if (*pid == 0)
        {
            arr = ft_strsplit((*ex)->cmd, ' ');
            if ((nw = (arr[2] == NULL) ? open(arr[1], O_RDONLY) : open(arr[2], O_RDONLY) ) == -1)
            {
                wait(0);
                printf("%i error_in_child\n", *pid);
                exit(0);
            }
            dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(arr[0])));
            close(nw);
            tmp = *ex;
            free_tab(arr);
            while (tmp->prev->type != 0  && tmp->prev->type != 42 && tmp->prev->type != 8)
                tmp = tmp->prev;
            if (tmp->prev->type == 0 && tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')) && wait(0))
                *env = exec_fct_nf(arr, *env);
            else 
                exit(0);
        }
        // else
        // {
        //     s->in = s->p[0];
        //     s->out = s->p[1];
        //     close (s->p[0]);
        //     close (s->p[1]);
        //     free_tab(arr);
        //     dup2(i, 0);
        //     close(i);
        // }
}



// void    redirecting_out_child(t_cmd **ex, t_env **env, int nw, pid_t *pid, t_exec *s)
// {
//     char       **arr;
//     t_cmd       *tmp;
//     int         i = 0;

//     if (*pid == 0)
//     {
//         arr = ft_strsplit((*ex)->cmd, ' ');
//         nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         i = dup(1);
//         dup2(nw, (arr[2] == NULL ? 1 : ft_atoi(arr[0])));
//         close(nw);
//         tmp = *ex;
//         free_tab(arr);
//         while (tmp->prev->type != 0  && tmp->prev->type != 42)
//             tmp = tmp->prev;
//         if (tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')))
//         {
//             wait(0);
//             *env = exec_fct_nf(arr, *env);
//             free_tab(arr);
//         }
//     }
//     else 
//     {
//         s->fd_in = s->p[0];
//         s->fd_out = s->p[1];
//         close (s->p[0]);
//         close (s->p[1]);
//         // dup2(i, 1);
//         dup2(1 ,i);
//         close(i);
//     }
// }

// void    redirecting_in_child(t_cmd **ex, t_env **env, int nw, pid_t *pid, t_exec *s)
// {
//     char        **arr = NULL;
//     t_cmd       *tmp;
//     int         i = 0;

//         if (*pid == 0)
//         {
//             arr = ft_strsplit((*ex)->cmd, ' ');
//             if ((nw = (arr[2] == NULL) ? open(arr[1], O_RDONLY) : open(arr[2], O_RDONLY) ) == -1)
//             {
//                 wait(0);
//                 printf("%i error_in_child\n", *pid);
//                 exit(0);
//             }
//             i = dup(0);
//             dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(arr[0])));
//             close(nw);
//             tmp = *ex;
//             free_tab(arr);
//             while (tmp->prev->type != 0  && tmp->prev->type != 42 && tmp->prev->type != 8)
//                 tmp = tmp->prev;
//             if (tmp->prev->type == 0 && tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')) && wait(0))
//                 *env = exec_fct_nf(arr, *env);
//             else 
//                 exit(0);
//         }
//         else
//         {
//             s->fd_in = s->p[0];
//             s->fd_out = s->p[1];
//             close (s->p[0]);
//             close (s->p[1]);
//             free_tab(arr);
//             dup2(i, 0);
//             close(i);
//         }
// }
