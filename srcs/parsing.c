#include "../twenty.h"

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

t_cmd   *sub_into_ex(char *s, int i, int in, t_cmd *ex) //sub and put into ex
{
    t_cmd   *nw;

    if (i == in)
        return (ex);
    if (ex->cmd == NULL && ex->prev->type == 42 && ex->next->type == 42)
    {
        ex->cmd = ft_strsub(s, in , i - in);
        ex->start = in;
    }
    else
    {
        while (ex->next != NULL)
            ex = ex->next;
        if (!(nw = (t_cmd*)malloc(sizeof(t_cmd))))
            return (NULL);
        nw->cmd = ft_strsub(s, in , i - in);
        ex->prev->next = nw;
        nw->next = ex;
        nw->start = in;
        nw->prev = ex->prev;
        ex->prev = nw;
    }
    // printf("");
    return (ex);
}


t_cmd   *separate_cmd(char *s, int i, int in ,t_cmd *ex) // sep word && metacharactere
{
    int     q;

    q = 0;
    if (!(s[i] != '&' && s[i] != '|' && s[i] != ';' && s[i] != '>' && s[i] != '<' ) && s[i])
    {
        printf("%c\n", s[i]);
        while (!(s[i] != '&' && s[i] != '|' && s[i] != ';' && s[i] != '>' && s[i] != '<' ) && s[i])
            ++i;
        ex = sub_into_ex(s, i, in, ex);
        in = i;
    }
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
        while (!(s[i] != '&' && s[i] != '|' && s[i] != ';' && s[i] != '>' && s[i] != '<' ) && s[i])
            ++i;
        ex = sub_into_ex(s, i, in, ex);
        in = i;
    }   
    return (ex);
}

void   join_ex(t_cmd **ex)
{
    char    *tmp;
    char    *tmp2;
    t_cmd   *ext;

    while ((*ex)->prev != NULL)
        *ex = (*ex)->prev;
    while ((*ex)->next != NULL)
    {
        if ((*ex)->type == 0 && (*ex)->next->type == 0)
        {
            tmp = ft_strjoin(" ", (*ex)->next->cmd);
            tmp2 = ft_strjoin((*ex)->cmd, tmp);
            free((*ex)->cmd);
            (*ex)->cmd = tmp2;
            (*ex)->next = (*ex)->next->next;
            (*ex)->next->prev = *ex;
        }
        else if ((*ex)->type == 8 || (*ex)->type == 7)
        {
            *ex = (*ex)->next;
            ext = (*ex)->prev;
            (*ex)->type = 8;
            (*ex)->prev->prev->next = *ex;
            (*ex)->prev = (*ex)->prev->prev;
            *ex = (*ex)->next;
            free(ext);
        }
        else
            *ex = (*ex)->next;
    }
}

void    join_re(t_cmd **ex)
{
    char    *tmp;
    char    *tmp2;
    

    while ((*ex)->prev != NULL)
        *ex = (*ex)->prev;
    while ((*ex)->next != NULL)
    {
        while ((*ex)->next != NULL)
        { 
            if (((*ex)->type == 8 || (*ex)->type == 7) && (*ex)->prev->type == 0 
                && (*ex)->next->type == 0) // ls > co > co
            {
                printf("%s && %s\n",(*ex)->prev->cmd, (*ex)->next->cmd);
                tmp = ft_strjoin(" ", (*ex)->next->cmd);
                tmp2 = ft_strjoin((*ex)->prev->cmd, tmp);
                printf("tmp->%s\n", tmp2);
                free((*ex)->prev->cmd);
                (*ex)->prev->cmd = tmp2;
                (*ex)->next->next->prev = *ex;                
                (*ex)->next = (*ex)->next->next;

            }
            *ex = (*ex)->next;
        }            
    }
}


int     parsing_op(char *s, t_cmd **ex) //get all op ctrl
{
    int     i;
        
    i = 0;
    while (s[i] && s[i] == ' ')
        ++i;
    *ex = separate_cmd(s, i, i, *ex); //separate by simple word and metacharactere
    i = parse_type(&(*ex)); // give at first a type as cmd(0) or a op ctrl(1)
    //parse variable environnement
    *ex = parse_op_int(*ex, s); // give all op ctrl specifique type and parse redirection proprely
    if ((i = parse_synthaxe(*ex)) != 0)
        return(i);
    join_ex(&(*ex)); //join les 0 ensemble
    join_re(&(*ex)); // join les cas ls -a > co -q ----> ls -a q > co
    // print_ex(*ex);
    // exit(0);
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

int     parsing(t_edit *ed, t_froz **fz, t_cmd **ex)
{
    char    *nw;

    nw = NULL;
    *ex = init_ex(NULL);
    (*fz)->cmd = join_cmd((*fz)->cmd, ed, *fz);
    while (ed->rpz[0] == 0)
        ed = ed->next;
    if (((*fz)->mode[3] = parsing_quote((*fz)->cmd))) //parsing_quote
        return(0);
    else if (((*fz)->mode[3] = parsing_op((*fz)->cmd, &(*ex)))) // parsing_op
    {
        if (!((*fz)->mode[3] >= 0 && (*fz)->mode[3] < 6))
        {
            printf("ERROR %i\n", (*fz)->mode[3]);
            (*fz)->mode[3] = 0;
        }
    }
    else if ((*fz)->mode[3] == 0)
        return(1);
    return(0);
}