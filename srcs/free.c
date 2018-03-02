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

int    free_kill(t_proc **p)
{
    int i;
    t_proc *tmp;

    while ((*p)->next != NULL)
    {
        kill((*p)->pid, SIGKILL);
        if ((i = kill((*p)->pid, SIGKILL)) == -1)
            break;
        tmp = *p;
        *p = (*p)->next;
        free(tmp);
    }
    return (i);
}

void    free_pid_loop(t_proc *p, int i)
{
    t_proc *tmp;
    
    if (i != -1)
    {
        kill(p->pid, SIGKILL);
        free(p);
    }
    else if (p)
    {
        while (p->next != NULL)
        {
            tmp = p;
            p = p->next;
            free(tmp);
        }
        free(p);
    }
}