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
    // printf("%s, %i, %i\n", s, i, nb);
    return (s);
}
