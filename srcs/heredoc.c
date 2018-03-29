#include "../twenty.h"

void    add_here_struct(t_froz *fz, char *s) //ajouter les limiteurs
{
    char    **t;
    t = ft_strsplit(s, ' ');
    if ((!fz->here->delim) && fz->here->prev == NULL &&  fz->here->next == NULL )
    {
        // printf("INIT %s\n", s);
        //add struct actuel
        fz->here->delim = ft_strdup(t[1]);
        fz->here->doc = NULL;
        fz->here->ok[0] = 0;
        fz->here->prev = NULL;
        //init here->next
        fz->here->next = (t_here*)malloc(sizeof(t_here));
        fz->here->next->prev = fz->here;
        fz->here = fz->here->next;
        fz->here->delim = NULL;
        fz->here->next = NULL;
    }
    else if (fz->here->delim == NULL)
    {
        // printf("HERE %s\n", s);
        fz->here->delim = ft_strdup(t[1]);
        fz->here->doc = NULL;
        fz->here->ok[0] = 0;
        //init here->next
        fz->here->next = (t_here*)malloc(sizeof(t_here));
        fz->here->next->prev = fz->here;
        fz->here = fz->here->next;
        fz->here->delim = NULL;
        fz->here->next = NULL;
    }
    else
        fz->here = fz->here->next;
    free_tab(t);
}

int     check_struct(t_froz *fz)    //check les heredocs completer ou pas
{
    while(fz->here->prev != NULL)
        fz->here = fz->here->prev;
    while (fz->here->delim != NULL && fz->here->ok[0] == 1)
        fz->here = fz->here->next;
    if (fz->here->delim == NULL && fz->here->next == NULL)
        fz->mode[3] = 0;
    else
        fz->mode[3] = 6;
    while(fz->here->prev != NULL)
        fz->here = fz->here->prev;
    return (fz->mode[3]);
}

int    add_delim(t_froz *fz, t_cmd *ex) // ajouter les limiteur
{
    fz->mode[3] = 6;
    while (ex->prev->prev != NULL)  //revenir au debut de la liste parse
        ex = ex->prev;
    while (ex->cmd != NULL)
    {
        // printf("->%s\n", fz->here->delim);
        if (ex->type == 6)              //if [<<]
            add_here_struct(fz, ex->cmd);
        ex = ex->next;
    }
    // print_here(fz);
    return (check_struct(fz));
}

void    add_doc_s(t_froz *fz, char *s)      //add doc
{
    int fd;

    fd = 0;
    if (ft_strcmp(s, fz->here->delim) == 0)
    {
        fz->here->ok[0] = 1;
        fd = open("/tmp/in", O_CREAT | O_RDWR | O_TRUNC, 0644);
        write(fd, fz->here->doc, ft_strlen(fz->here->doc));
        close(fd);
        free(s);
    }
    else if (fz->here->doc == NULL)
        fz->here->doc = s;
    else
        fz->here->doc = strjoin_free(strjoin_free(fz->here->doc, "\n", 1), s, 3);

}

int    add_doc(t_froz *fz, char *s)
{
    while (fz->here->prev != NULL)
        fz->here = fz->here->prev;
    while (fz->here->ok[0] == 1)
        fz->here = fz->here->next;
    add_doc_s(fz, s);
    // print_here(fz);
    while (fz->here->prev != NULL)
        fz->here = fz->here->prev;
    return (0);
}