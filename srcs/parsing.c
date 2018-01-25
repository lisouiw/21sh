#include "../twenty.h"

//quote laisse en raw
//dquote interprete certaine variable

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
    if (parsing_quote)
        exit(0);
    if (ed->c[0] == 39)
        (*fz)->mode[3] = 1;
    else if (ed->c[0] == 34)
        (*fz)->mode[3] = 2;
    else if (ed->c[0] == '|')
        (*fz)->mode[3] = 3;
    else if (ed->c[0] == '&')
        (*fz)->mode[3] = 4;
    else if (ed->c[0] == 'o')
        (*fz)->mode[3] = 5;
    else if (ed->c[0] == '>') 
        (*fz)->mode[3] = 6;
    else
    {
        (*fz)->mode[3] = 0;
        return(1);
    }
    return(0);
}