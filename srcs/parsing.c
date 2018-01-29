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
    // <    ->  [n]<


    // Redirecting Input 7
        // [n]<word
    // Redirecting Output 8
        // [n]>word
    // Appending Redirected Output 9
        //  [n]>>word
    // Redirecting Standard Output and Standard Error 10
        // &>word      >&word   :   >word 2>&1
    // Here Documents 6
        // <<[-]word
    // Duplicating File Descriptors 11
        // [n]<&word   [n]>&word
    // Moving File Descriptors 12
        // [n]<&digit-   [n]>&digit-


// }
t_cmd   *parse_ampersand(t_cmd *ex, char *s)
{
    if (ft_strcmp(ex->cmd, "&&") == 0)
        ex->type = 4;
    else if (ft_strcmp(ex->cmd, ">&") == 0 || ft_strcmp(ex->cmd, "&>") == 0 ||ft_strcmp(ex->cmd, "<&") == 0) || ft_strcmp(ex->cmd, "&<") == 0)
        ex = parse_redirec(ex, s);
    else
        ex->type = 1;    
    // else if (ft_strcmp(ex->cmd, "||") == 0)
    
    
    return (ex);
}

t_cmd   *parse_pipe_or(t_cmd *ex)
{
    if (ft_strcmp(ex->cmd, "|") == 0)
        ex->type = 3;
    else if (ft_strcmp(ex->cmd, "||") == 0)
        ex->type = 5;
    else
        ex->type = -1;
    return (ex);
}

t_cmd   *giv_type(t_cmd *ex, char *s)
{
    if (ex->cmd[0] == '&')
        ex = parse_pipe_or(ex);
    else if (ex->cmd[0] == '&')
        ex = parse_ampersand(ex, s);

    // else if (ex->cmd[0] == '')
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

void    print_ex(t_cmd *ex)
{
    while (ex->prev != NULL)
        ex = ex->prev;
    printf("----------------------------------\n");    
    while (ex->next != NULL)
    {
        printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
        ex = ex->next;
    }
    printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
    printf("----------------------------------\n");  
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

t_cmd   *sub_into_ex(char *s, int i, int in, t_cmd *ex) //sub and put into ex
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
    ex->start = in;
    return (ex);
}


t_cmd   *separate_cmd(char *s, int i, int in ,t_cmd *ex) // sep word && metacharactere
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

int     parsing_op(char *s, t_cmd **ex) //get all op ctrl
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
    *ex = separate_cmd(s, i, i, *ex); //separate by simple word and metacharactere
    i = parse_type(&(*ex)); // give at first a type as cmd(0) or a op ctrl(1)
    ex = parse_op_int(*ex, s); // give all op ctrl specifique type and parse redirection proprely
    print_ex(*ex);
    return (0);
}

int     parsing_quote(char *s) //if all quotes are closed
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