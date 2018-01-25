#include "../twenty.h"

//quote laisse en raw
//dquote interprete certaine variable


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
    char *nw;

    nw = NULL;
    if ((*fz)->cmd == NULL)
        (*fz)->cmd = ed_str(ed, NULL, (*fz)->nb[0] - giv_last(*fz));
    else 
    {
        if (ed->rpz[0] == 1 && ed->rpz[1] == 1)
            (*fz)->cmd = ft_strjoin((*fz)->cmd, "\n\0");  
        else
        {
            nw = ft_strjoin("\n", ed_str(ed, NULL, (*fz)->nb[0] - giv_last(*fz)));
            (*fz)->cmd = ft_strjoin((*fz)->cmd, nw);  
        }
    }
    while (ed->rpz[0] == 0)
        ed = ed->next;
    if (((*fz)->mode[3] = parsing_quote((*fz)->cmd)))
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