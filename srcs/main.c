#include "../twenty.h"

/*
        A fix:
        - Lancez la commande "$> cd /tmp; sort << EOF | cat -e > sorted_poem ;
        sed -e 's/Roses/Turnips/' < sorted_poem > better_poem; cd -;
        echo "I prefer turnips anyway" >> /tmp/better_poem; cat /tmp/better_poem"
        et entrez le poème suivant à l'invite du heredoc (sans les triple guillemets) :
        """
        Roses are red
        Violets are blue
        All my base are belong to you
        I love you
        """
        La sortie doit être (toujours sans les triples guillemets) :
        """
        All my bases are belong to you$
        I love you$
        Turnips are red$
        Violets are blue$
        I prefer turnips anyway
        """

        //////////////////////////////////FIX//////////////////////////////


        - Lancez la commande "$> cat -e << EOF", puis entrez le texte
        suivant sans les triples guillemets mais en respectant les
        sauts de lignes :
        """
        Roses are red
        Violets are blue
        All my base are belong to you
        And so are you
        """
        Appuyez ensuite sur ctrl+d pour terminer votre entrée.
        La sortie de la commande doit être exactement :
        Roses are red
        Violets are blue
        All my base are belong to you
        And so are you


        - Lancez la commande "$> cat", tapez quelques caractères puis
        appuyez sur ctrl+D deux fois. Le premier appui doit afficher
        les caractères tapés, le second doit rendre le prompt.

*/


int         main(void)
{
    t_env   *env = NULL;

    g_nb = init_shell(&fz, &env, &ed, &hs);
    while (42)
    {
        ls_signal(fz->mode[3]);
        read(0, &fz->buf, 4);
        // printf("%i %i %i\n", fz->buf[0], fz->buf[1], fz->buf[2]);
        // exit(0);
        if (fz->buf[0] == 10)//touch enter
        {
            cursor_end(ed);                             //remettre le curseur a la fin pour les calculs
            env = treat_cmd(env, &ed, &hs, &fz);        //traiter la cmd
            init_for_new(&hs, &fz, &ed);                // init ed et mettre le prompt approprie
        }
        else if (fz->buf[0] == 3)                       //ctrl-C rendre le prompt
        {
            write(1, "\n", 1);
            init_for_new(&hs, &fz, &ed);                // init ed et mettre le prompt approprie        
        }
        else if (fz->buf[0] == 0 && fz->buf[1] ==  0 && fz->buf[2] == 0) //cat -e | ./21sh
            free_for_exit();
        else
            ed = touch(&ed, &fz, &hs);                  //add les touch -> ed
        init_data(&fz);
    }
}

void    cursor_end(t_edit *ed)               //remettre le curseur a la fin pour les calculs       
{
    int     i;
    
    tputs(tgetstr("rc", NULL), 0, ft_put);
    while (ed->rpz[1] == 0)
        ed = ed->next;
    i = ed->rpz[3];
    if (i % g_nb->tb[0] == 1)
        put_my_cur(g_nb->tb[0], 'D');
    else
        put_my_cur(g_nb->tb[0], 'C');
    if (i > g_nb->tb[0] && i % g_nb->tb[0] == 0)
        put_my_cur(((i / g_nb->tb[0]) - 1), 'B');
    else if (i > (g_nb->tb[0]))
        put_my_cur((i / g_nb->tb[0]), 'B');
    init();
        
}

void    put_my_cur(int nb, char c)
{
    char    *i;

    i = ft_itoa(nb);
    ft_putstr("\033[");
    ft_putstr(i);
    ft_putchar(c);
    free(i);
}