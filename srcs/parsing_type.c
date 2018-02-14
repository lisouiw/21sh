#include "../twenty.h"

int     parse_synthaxe(t_cmd *ex)
{
    int     i;
    while (ex->prev != NULL)
        ex = ex->prev;
    ex = ex->next;
    i = ex->type;
    if (i == 3 | i == 4 || i == 5 || i == 13 )
            return (-1);
    while (ex->next != NULL)
    {
        if ((ex->type == 3 || ex->type == 4 || ex->type == 5 ) && ex->prev->type == 0 && ex->next->type == 42)
            return (ex->type); // pipe, and , or    cmd1 [op] cmd2
        else if ((ex->type == 3 || ex->type == 4 || ex->type == 5 ) && ex->prev->type != 0 && ex->next->type != 0)
            return (-1); // pipe, and , or    cmd1 [op] cmd2
        else if ((ex->type == 6 || ex->type == 7 || ex->type == 8 || ex->type == 9 || ex->type == 10 || ex->type == 11) && ex->next->type != 0)
            return (-1); // <<,  <, >, >>, >&, <& word
        else if (ex->type == 13 && ex->prev->type != 0)
            return (-1); // cmd [;]
        else if (ex->type == -1)
            return (-1); // cmd [;]
        ex = ex->next;
    }
    return (0);
}

t_cmd   *giv_type(t_cmd *ex, char *s)
{
    if (ex->cmd[0] == '|')
        ex = parse_pipe_or(ex);
    else if (ex->cmd[0] == '&')
        ex = parse_ampersand(ex);
    else if (ex->cmd[0] == '<')
        ex = parse_less_than(ex, s); // probleme
    else if (ex->cmd[0] == '>')
        ex = parse_great_than(ex, s);
    else if (ex->cmd[0] == ';')
        ex->type = ft_strcmp(ex->cmd, ";")  == 0 ? 13 : -1;
    else if (if_only(ex->cmd, '\n') == 1)
        ex->type = 14;
    return (ex);
}

t_cmd   *parse_op_int(t_cmd *ex, char *s) // give op ctrl specifique type and 
{
    while (ex->next != NULL)
    {
        if (ex->type == 1)
            ex = giv_type(ex, s);
        ex = ex->next;
    }
    while (ex->prev != NULL) // debut de la chaine 
        ex = ex->prev;
    return (ex);
}

int     parse_type(t_cmd **ex) // give at first a type
{
    char    c;

    while ((*ex)->prev->cmd != NULL)
        *ex = (*ex)->prev;
    while ((*ex)->cmd != NULL)
    {
        c = (*ex)->cmd[0];
        if ( c == '&' || c == '|' || c == ';' || c == '>' || c == '<' || if_only((*ex)->cmd, '\n') == 1)
            (*ex)->type = 1;
        else
            (*ex)->type = 0;
        *ex = (*ex)->next;
    }
    while ((*ex)->prev != NULL)
        *ex = (*ex)->prev;
    return (0);
}