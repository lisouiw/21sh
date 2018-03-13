#include "../twenty.h"

void    free_ex(t_cmd **ex)
{
    if (*ex != NULL)
        free(*ex);
    return;
}

void    free_all_ex(t_cmd **ex)
{
    t_cmd   *tmp;

    while ((*ex)->next != NULL)
        *ex = (*ex)->next;
    while ((*ex)->prev != NULL)
    {
        tmp = (*ex)->prev;
        free((*ex)->cmd);
        free(*ex);
        *ex = tmp;
    
    }
    free((*ex)->cmd);
    free(*ex);
}