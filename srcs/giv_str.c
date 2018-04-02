#include "../twenty.h"

char    *ed_str(t_edit *cmd, char *s, int nb)
{
    int     i;

    i = -1;
    while (cmd->rpz[0] == 0)
        cmd = cmd->next;
    if (!(s = (char*)malloc((nb + 1)* sizeof(char))))
        return (NULL);
    while (++i < nb)
    {
        s[i] = cmd->c[0];
        cmd = cmd->next;
    }
    s[i] = '\0';
    return (s);
}

char    *join_cmd_nw(char *cmd, t_edit *ed, t_froz *fz)
{
    char *nw;
    char *tmp;
    
    nw = NULL;
    if (cmd == NULL)
        cmd = ed_str(ed, NULL, fz->nb[0] - giv_last(fz));
    else 
    {
        if (ed->rpz[0] == 1 && ed->rpz[1] == 1)
            tmp = ft_strjoin(cmd, "\n");  
        else
        {
            nw = ft_strjoin_free("\n", ed_str(ed, NULL, fz->nb[0] - giv_last(fz)), 2);
            tmp = ft_strjoin_free(cmd, nw, 2);  
        }
        free(cmd);
        return (tmp);
    }
    return (cmd);
}

char    *join_cmd(char *cmd, t_edit *ed, t_froz *fz)
{
    char *nw;
    char *tmp;
    
    nw = NULL;
    if (cmd == NULL)
        cmd = ed_str(ed, NULL, fz->nb[0] - giv_last(fz));
    else 
    {
        if (ed->rpz[0] == 1 && ed->rpz[1] == 1)
            tmp = ft_strjoin(cmd, "\0");  
        else
        {
            nw = ed_str(ed, NULL, fz->nb[0] - giv_last(fz));
            tmp = ft_strjoin_free(cmd, nw, 2);  
        }
        free(cmd);
        return (tmp);
    }
    return (cmd);
}