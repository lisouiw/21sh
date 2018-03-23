#include "../twenty.h"

void    redirection(t_cmd **ex, t_env **env, t_exec *s)
{
    char    **arr;
    
    if (s)
        ;
    arr = ft_strsplit((*ex)->cmd, ' ');
    *ex = (*ex)->next;
    if (redirection_check_create(*ex))
        redirecting_exec(ex, env, arr);
    else
        exit(0);
    free_tab(arr);
}

void    redirection_fork(t_cmd **ex, t_env **env, t_exec *s)
{
    char    **arr;
    pid_t   pid;

    if (s || env)
        ;
    arr = ft_strsplit((*ex)->cmd, ' ');
    *ex = (*ex)->next;
    if ((pid = fork()) == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
    {
        if (redirection_check_create(*ex))
            redirecting_exec(ex, env, arr);
        else
            exit(0);
    }
    free_tab(arr);
}


char    **heredoc_fct(t_cmd *ex)
{
    printf("[%s]\n", ex->cmd);
    // exit(0);
    return (NULL);
}

char    **give_seven(t_cmd *ex)
{
    // while (ex->next->type == 6 || ex->next->type == 7 || ex->next->type == 8 || ex->next->type == 9 || ex->next->type == 10 || ex->next->type == 11)
    while (ex->next->type >= 6 &&  ex->next->type <= 11)
        ex = ex->next;
    while (ex->type == 8 || ex->type == 9 || ex->type == 10 || ex->type == 11)
        ex = ex->prev;
    if (ex->type != 7)
        return (NULL);
    return (ft_strsplit(ex->cmd, ' '));
}

void    redirecting_exec(t_cmd **ex, t_env **env, char **arr)
{
    int         nw;
    char        **tmp;
    
    if ((tmp = give_seven(*ex)) != NULL)
    {
        nw = (tmp[2] == NULL) ? open(tmp[1], O_RDONLY) : open(tmp[2], O_RDONLY);
        dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(tmp[0])));
        
    }
    wait(0);
    *env = exec_fct_nf(arr, *env); //EXECUTION
}