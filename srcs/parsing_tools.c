#include "../twenty.h"

int     isnumber(char *s)
{
    int i;

    i = -1;
    while (s[++i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (0);
    }
    return (1);
}

void    print_ex(t_cmd *ex)
{
    while (ex->prev != NULL)
        ex = ex->prev;
    printf("-------------DEBUT---------------------\n");    
    while (ex->next != NULL)
    {
        printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
        ex = ex->next;
    }
    printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
    printf("----------------------------------\n");    
    printf("----------------------------------\n");  
    while (ex->prev != NULL)
    {
        printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
        ex = ex->prev;
    }
    printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
    printf("------------FIN----------------------\n");  
}

void    print_ex_up(t_cmd *ex)
{
    while (ex->prev != NULL)
        ex = ex->prev;
    printf("-------------DEBUT---------------------\n");    
    while (ex->next != NULL)
    {
        printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
        ex = ex->next;
    }
    printf("[%s]->[%i][%i]\n", ex->cmd, ex->type, ex->start);
    printf("----------------------------------\n");    
}