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
    return (ex);
}


t_cmd   *separate_cmd(char *s, int i, int in ,t_cmd *ex) // sep word && metacharactere
{
    int     q;

    q = 0;
    if (!(s[i] != '&' && s[i] != '|' && s[i] != ';' && s[i] != '>' && s[i] != '<' ) && s[i])
    {
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
    t_cmd   *cmd;

    while ((*ex)->prev != NULL)
        *ex = (*ex)->prev;
    while ((*ex)->next != NULL)
    {
        if ((*ex)->type == 0 && (*ex)->next->type == 0)
        {
            cmd = (*ex)->next;
            tmp = ft_strjoin(" ", (*ex)->next->cmd);
            tmp2 = ft_strjoin((*ex)->cmd, tmp);
            free((*ex)->cmd);
            (*ex)->cmd = tmp2;
            (*ex)->next = (*ex)->next->next;
            (*ex)->next->prev = *ex;
            free(tmp);
            free(cmd);
            free(cmd->cmd);
        }
        else
            *ex = (*ex)->next;
    }
}

void    join_redirecting2(t_cmd **join, t_cmd **ex)
{
    char    *tmp;
    char    *tmp2;
    t_cmd   *cmd;

    while ((*ex)->type == 8 || (*ex)->type == 7||  (*ex)->type == 9)
    {
        *ex = (*ex)->next;
        if ((*ex)->type == 0)
        {
            tmp = ft_strjoin((*join)->cmd, " ");
            tmp2 = ft_strjoin(tmp, (*ex)->cmd);
            free((*join)->cmd);
            (*join)->cmd = tmp2;
            cmd = *ex;
            *ex = (*ex)->next;
            (*ex)->prev = (*ex)->prev->prev;
            (*ex)->prev->next = (*ex);
            free(tmp);
            free(cmd->cmd);
            free(cmd);
        }
    }
}

void    join_redirecting(t_cmd **ex)
{
    while ((*ex)->prev != NULL)
        *ex = (*ex)->prev;
    while ((*ex)->next != NULL)
    {
        while ((*ex)->next != NULL)
        { 
            if (((*ex)->type == 8 || (*ex)->type == 7 || (*ex)->type == 9) && (*ex)->prev->type == 0)// ls > co > co
                join_redirecting2(&(*ex)->prev, &(*ex));
            if ((*ex)->next != NULL)
                *ex = (*ex)->next;
        }            
    }
}


int     parsing_op(char *s, t_cmd **ex, t_env *env) //get all op ctrl
{
    int     i;
        
    i = 0;
    if (env)
        ;
    while (s[i] && s[i] == ' ')
        ++i;
    // ecriture_info(env);
    s = quote_variable(s, NULL, env);
    *ex = separate_cmd(s, i, i, *ex);   //separate by simple word and metacharactere
    i = parse_type(&(*ex));             // give at first a type as cmd(0) or a op ctrl(1)
                                        //parse variable environnement
    *ex = parse_op_int(*ex, s);         // give all op ctrl specifique type 
                                        //and parse redirection proprely
    if ((i = parse_synthaxe(*ex)) != 0)
        return(i);
    print_ex_up(*ex);
    join_redirecting(&(*ex));           // join les cas ls -a > co -q ----> ls -a q > co
    join_ex(&(*ex));                    //join les 0 ensemble
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

int     parsing(t_edit *ed, t_froz **fz, t_cmd **ex, t_env *env)
{
    char    *nw;

    nw = NULL;
    *ex = init_ex(NULL);
    (*fz)->cmd = join_cmd((*fz)->cmd, ed, *fz);
    while (ed->rpz[0] == 0)
        ed = ed->next;
    if (((*fz)->mode[3] = parsing_quote((*fz)->cmd))) //parsing_quote
        return(0);
    else if (((*fz)->mode[3] = parsing_op((*fz)->cmd, &(*ex), env))) // parsing_op
    {
        free_all_ex(&(*ex));
        if (!((*fz)->mode[3] >= 0 && (*fz)->mode[3] < 6)) // autre && || |
        {
            printf("ERROR %i\n", (*fz)->mode[3]);
            (*fz)->mode[3] = 0;
        }
        else 
        {
            free((*fz)->cmd);
            (*fz)->cmd = NULL;
        }
    }
    else if ((*fz)->mode[3] == 0)
        return(1);
    return(0);
}