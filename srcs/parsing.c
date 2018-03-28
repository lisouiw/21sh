#include "../twenty.h"

t_cmd   *sub_into_ex(char *s, int i, int in, t_cmd *ex) //sub and put into ex
{
    t_cmd   *nw;
    char    *tmp;

    if (i == in)
        return (ex);
    if (ex->cmd == NULL && ex->prev->type == 42 && ex->next->type == 42)
    {
        in = in  + white_space(tmp = ft_strsub(s, in , i - in));
        free(tmp);
        ex->cmd = ft_strsub(s, in , i - in);
        ex->start = in;
    }
    else
    {
        while (ex->next != NULL)
            ex = ex->next;
        if (!(nw = (t_cmd*)malloc(sizeof(t_cmd))))
            return (NULL);
        in = in  + white_space(tmp = ft_strsub(s, in , i - in));
        free(tmp);
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

    // while ((*ex)->type == 8 || (*ex)->type == 7|| *ex)->type == 9 ||  (*ex)->type == 10)
    while ((*ex)->type >= 6 && (*ex)->type <= 11)
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
            // if (((*ex)->type == 8 || (*ex)->type == 7 || (*ex)->type == 9 || (*ex)->type == 10) && (*ex)->prev->type == 0)// ls > co > co
            if ((*ex)->type >= 6 && (*ex)->type <= 11)

                join_redirecting2(&(*ex)->prev, ex);
            if ((*ex)->next != NULL)
                *ex = (*ex)->next;
        }            
    }
}


int     parsing_op(char *s, t_cmd **ex, t_env *env, t_froz *fz) //get all op ctrl
{
    int     i;
        
    i = 0;
    if (fz)
        ;
    while (s[i] && s[i] == ' ')
        ++i;
    s = quote_variable(s, NULL, env);
    *ex = separate_cmd(s, i, i, *ex);   //separate by simple word and metacharactere
    i = parse_type(ex);                 // give at first a type as cmd(0) or a op ctrl(1)
                                        //parse variable environnement
    *ex = parse_op_int(*ex, s);         // give all op ctrl specifique type | join n>&n
    // print_ex_up(*ex);
    if ((i = parse_synthaxe(*ex)) != 0)
    {
        free(s);
        return(i);
    }
    join_redirecting(ex);           // join les cas ls -a > co -q ----> ls -a q > co
    join_ex(ex);                    //join les 0 ensemble
    print_ex_up(*ex);
    free(s);
    return (add_delim(fz, *ex));
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

int     parsing(t_edit *ed, t_froz *fz, t_cmd **ex, t_env *env)
{
    *ex = init_ex(NULL);
    if (fz->mode[3] == 6)   //if mode heredoc , no save in fz->cmd else if yes
        add_doc(fz, ed_str(ed, NULL, fz->nb[0] - giv_last(fz)));
    else
        fz->cmd = join_cmd_nw(fz->cmd, ed, fz); //join avec \n
    while (ed->rpz[0] == 0) // position: debut de la liste
        ed = ed->next;
    if ((fz->mode[3] = parsing_quote(fz->cmd))) //parsing_quote
    {
        free_all_ex(ex);
        return(0);
    }
    else if ((fz->mode[3] = parsing_op(ft_strdup(fz->cmd), ex, env, fz))) // parsing_op
    {
        free_all_ex(&(*ex));
        if (!(fz->mode[3] >= 0 && fz->mode[3] <= 6)) // autre que && || |
        {
            printf("ERROR %i\n", fz->mode[3]);
            // free(fz->cmd);
            // fz->cmd = NULL;
            fz->mode[3] = 0;
            return(0);
        }
    }
    else if (fz->mode[3] == 0)
    {
        // printf("PARSING OK\n");
        return(1);
    }
    return(0);
}






// void    add_here_struct(t_froz *fz, char *s)
// {
//     char    **t;

//     t = ft_strsplit(s, ' ');
//     if (fz->here == NULL)
//     {
//         fz->here = (t_here*)malloc(sizeof(t_here));
//         fz->here->delim = ft_strdup(t[1]);
//         fz->here->doc = NULL;
//         fz->here->ok = 0;
//         fz->here->next = NULL;
//     }
//     else if (fz->here->delim == NULL)
//     {
//         fz->here = (t_here*)malloc(sizeof(t_here));
//         fz->here->delim = ft_strdup(t[1]);
//         fz->here->doc = NULL;
//         fz->here->ok = 0;
//         fz->here->next = NULL;
//     }
//     free_tab(t);
//     fz->here = fz->here->next;
// }