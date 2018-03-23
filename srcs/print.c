#include "../twenty.h"

void    print_here(t_froz *fz)
{
    printf("======PRINT_HEREDOC===========\n");
    while(fz->here->next != NULL)
    {
        printf("%s\n", fz->here->delim);
        fz->here = fz->here->next;
    }
    // printf("%s\n", fz->here->delim);
}