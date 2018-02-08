#include "../twenty.h"

t_cmd   *parse_redirec(t_cmd *ex, char *s)
{
    t_cmd   *tmp;

    tmp = ex->prev;
    if (ex->prev->cmd == NULL)
        return(ex);
    if (ex->prev != NULL && isnumber(ex->prev->cmd) && s[ex->start -1] != ' ')
    {
        ex->cmd = ft_strjoin(ex->prev->cmd, ex->cmd);
        ex->prev->prev->next = ex;
        ex->prev = ex->prev->prev;
        free(tmp->cmd);
        free(tmp);
    }
    return (ex);
}

t_cmd   *parse_ampersand(t_cmd *ex, char *s)
{
    if (ft_strcmp(ex->cmd, "&&") == 0)
        ex->type = 4;
    else if (ft_strcmp(ex->cmd, "&>") == 0) 
    {
        ex = parse_redirec(ex, s);
        ex->type = 10;        
    }
    else if (ft_strcmp(ex->cmd, "&<") == 0)
    {
        ex = parse_redirec(ex, s);
        ex->type = 11;        
    }
    else
        ex->type = -1;    
    return (ex);
}

t_cmd   *parse_great_than(t_cmd *ex, char *s)
{
    if (ft_strcmp(ex->cmd, ">") == 0)
    {
        ex->type = 8;
        ex = parse_redirec(ex, s);
    }
    else if (ft_strcmp(ex->cmd, ">>") == 0)
        ex->type = 9;        
    else if (ft_strcmp(ex->cmd, ">&") == 0 )
    {
        ex->type = 10;        
        ex = parse_redirec(ex, s);
    }
    else
        ex->type = -1;    
    return (ex);
}

t_cmd   *parse_less_than(t_cmd *ex, char *s)
{
    if (ft_strcmp(ex->cmd, "<") == 0)
    {
        ex->type = 7;
        ex = parse_redirec(ex, s);
    }
    else if (ft_strcmp(ex->cmd, "<<") == 0)
        ex->type = 6;        
    else if (ft_strcmp(ex->cmd, "<&") == 0 )
    {
        ex->type = 11;        
        ex = parse_redirec(ex, s);
    }
    else
        ex->type = -1;    
    return (ex);
}

t_cmd   *parse_pipe_or(t_cmd *ex)
{
    if (ft_strcmp(ex->cmd, "|") == 0) // prompt
        ex->type = 3;
    else if (ft_strcmp(ex->cmd, "||") == 0) // prompt
        ex->type = 5;
    else
        ex->type = -1;
    return (ex);
}