#include "../twenty.h"

///////// POur printf ex

    // while (ex->prev != NULL)
    //     ex = ex->prev;
    // printf("----------------------------------\n");    
    // while (ex->next != NULL)
    // {
    //     printf("%s\n", ex->cmd);
    //     ex = ex->next;
    // }
    // printf("%s\n", ex->cmd);
    // printf("----------------------------------\n");    

/////////////////////////////////////////////////////////

// && 
// ||
// |
// ;
// ' '
// >>
// <<
// &>
//

//quote laisse en raw
//dquote interprete certaine variable

// int     parsing_elem(t_cmd *ex)
// {

    // | = 3;
    // && = 4;
    // || = 5;
    // << = 6;  <<[-]word


    // >>
    // &> >&    ->     >&word        &>word    >word 2>&1
    //              [n]<&word    [n]>&word
    //              [n]<&digit-  [n]>&digit-
    // >    ->  [n]>word
    // <    ->  [n]<word


// }

void    print_ex(t_cmd *ex)
{
    while (ex->prev != NULL)
        ex = ex->prev;
    printf("----------------------------------\n");    
    while (ex->next != NULL)
    {
        printf("[%s]->%i\n", ex->cmd, ex->type);
        ex = ex->next;
    }
    printf("[%s]->%i\n", ex->cmd, ex->type);
    printf("----------------------------------\n");  
}

int     parse_type(t_cmd **ex)
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

t_cmd   *sub_into_ex(char *s, int i, int in, t_cmd *ex)
{
    t_cmd   *nw;

    if (i == in)
        return (ex);
    if (ex->cmd == NULL)
        ex->cmd = ft_strsub(s, in , i - in);
    else
    {
        if (!(nw = (t_cmd*)malloc(sizeof(t_cmd))))
            return (NULL);
        nw->cmd = ft_strsub(s, in , i - in);
        ex->next = nw;
        nw->prev = ex;
        nw->next = NULL;
        ex = ex->next;
    }
    return (ex);
}


t_cmd   *separate_cmd(char *s, int i, int in ,t_cmd *ex)
{
    int     q;

    q = 0;
    while (s[i])
    {
        while ((s[i] && (s[i] != '&' && s[i] != '|' && s[i] != ';' && s[i] != ' ' && s[i] != '>' && s[i] != '<')) || (s[i] && q != 0))
        {
            if (s[i] == 39 && q != 2)
                q = (q == 0) ? 1 : 0;
            else if (s[i] == '"' && q != 1)
                q = (q == 0) ? 2 : 0;
            ++i;
        }
        ex = sub_into_ex(s, i, in, ex);
        in = i;
        while (s[i] == ' ')
            ++i;
        in = i;
        while (!(s[i] != '&' && s[i] != '|' && s[i] != ';' && s[i] != '>' && s[i] != '<') && s[i])
            ++i;
        ex = sub_into_ex(s, i, in, ex);
        in = i;
    }
    return (ex);
}

int     parsing_op(char *s, t_cmd **ex)
{

    int     i;

    i = 0;
    if (!(*ex = (t_cmd*)malloc(sizeof(t_cmd))))
        return (0);
    (*ex)->cmd = NULL;
    (*ex)->type = 0;
    (*ex)->next = NULL;
    (*ex)->prev = NULL;
    while (s[i] == ' ')
        ++i;
    *ex = separate_cmd(s, i, i, *ex);
    i = parse_type(&(*ex));
    print_ex(*ex);
    return (0);
}

int     parsing_quote(char *s)
{
    int     i;
    int     a;

    i = 0; 
    a = -1;     
    while (s[++a])
    {
        if (s[a] == '"' && i != 1)
            i = (i == 0) ? 2 : 0;
        else if (s[a] == 39 && i != 2)
            i = (i == 0) ? 1 : 0;
    }
    return (i);
}

int     parsing(t_edit *ed, t_froz **fz)
{
    char    *nw;
    t_cmd   *ex;

    nw = NULL;
    ex = NULL;
    (*fz)->cmd = join_cmd((*fz)->cmd, ed, *fz);
    while (ed->rpz[0] == 0)
        ed = ed->next;
    if (((*fz)->mode[3] = parsing_quote((*fz)->cmd))) //parsing_quote
        ;
    else if (((*fz)->mode[3] = parsing_op((*fz)->cmd, &ex))) // parsing_op
        ;
    // else if (ed->c[0] == '|')
    //     (*fz)->mode[3] = 3;
    // else if (ed->c[0] == '&')
    //     (*fz)->mode[3] = 4;
    // else if (ed->c[0] == 'o')
    //     (*fz)->mode[3] = 5;
    // else if (ed->c[0] == '>') 
    //     (*fz)->mode[3] = 6;
    else if ((*fz)->mode[3] == 0)
    {
        // (*fz)->mode[3] = 0;
        return(1);
    }
    return(0);
}