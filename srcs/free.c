#include "../twenty.h"

void    free_ex(t_cmd **ex)
{
    if (*ex != NULL)
        free(*ex);
    return;
}