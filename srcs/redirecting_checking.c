#include "../twenty.h"


int     parsing_dup_out(char *s, int n, t_cmd *ex)
{
    size_t     len;
    int         fd;
    if (ex)
        ;
    if ((len = isnumber_len(s)) + 1 == ft_strlen(s) && s[len] == '-')
    {
        s[len] = '\0';
        dup2(ft_atoi(s), n);
        // redirection_check_create(ex->next);    
        close(n);
    }
    else
    {
        fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(fd, n);
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
        dup2(n, ft_atoi(s));
        // redirection_check_create(ex->next);        
        close(ft_atoi(s));
    }
    else
    {
        len = open(s, O_RDONLY);
        dup2(n, len);
    }
    return(1);
}



int     redirection_check_create(t_cmd *ex)
{
    while ((ex)->type >= 6 && (ex)->type <= 11)
    {
        if ((ex)->type == 8 || (ex)->type == 9) //creer les fichier
            redirection_file_create(ex);
        else if ((ex)->type == 7 && redirection_file_check(ex) == 0) //verif exist. Si non, exit.
                return (0);
        else if (ex->type == 10) // >&
            aggregation_out(ft_strsplit(ex->cmd, ' '), ex);
        else if (ex->type == 11) // <&
            aggregation_in(ft_strsplit(ex->cmd, ' '), ex);
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
        nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_RDWR | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_RDWR| O_TRUNC, 0644);
    else // ex->type == 9
        nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_RDWR | O_APPEND, 0644) : open(arr[2], O_CREAT | O_RDWR | O_APPEND, 0644);
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