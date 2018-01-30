#include "../twenty.h"

t_cmd   *giv_type(t_cmd *ex, char *s)
{
    if (ex->cmd[0] == '|')
        ex = parse_pipe_or(ex);
    else if (ex->cmd[0] == '&')
        ex = parse_ampersand(ex, s);
    else if (ex->cmd[0] == '<')
        ex = parse_less_than(ex, s);
     else if (ex->cmd[0] == '>')
        ex = parse_great_than(ex, s);
    else if (ex->cmd[0] == ';')
        ex->type = 13;
    // else if (ex->cmd[0] == '')
    // else if (ex->cmd[0] == '')
    // else if (ex->cmd[0] == '')
    // else if (ex->cmd[0] == '')
    return (ex);
}

t_cmd   *parse_op_int(t_cmd *ex, char *s) // give op ctrl specifique type and 
{
    while (ex->prev != NULL) // debut de la chaine 
        ex = ex->prev;
    while (ex->next != NULL)
    {
        if (ex->type == 1)
            ex = giv_type(ex, s);
        ex = ex->next;
    }
    if (ex->type == 1)
        ex = giv_type(ex, s);
    while (ex->prev != NULL) // debut de la chaine 
        ex = ex->prev;
    return (ex);
}

int     parse_type(t_cmd **ex) // give at first a type
{
    char    c;

    while ((*ex)->prev != NULL)
        *ex = (*ex)->prev;
    while ((*ex)->next != NULL)
    {
        c = (*ex)->cmd[0];
        if ( c == '&' || c == '|' || c == ';' || c == '>' || c == '<')
            (*ex)->type = 1;
        else
            (*ex)->type = 0;
        *ex = (*ex)->next;
    }
    c = (*ex)->cmd[0];
    if ( c == '&' || c == '|' || c == ';' || c == '>' || c == '<')
        (*ex)->type = 1;
    else
        (*ex)->type = 0;
    return (0);
}