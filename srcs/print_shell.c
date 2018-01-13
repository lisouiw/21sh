#include "../twenty.h"

int		ft_put(int c)
{
		write(0, &c, 1);
		return (1);
}

void	my_tputs(t_edit *ed)
{
	// if (ed->rpz[4] == 1)
	// 	tputs(tgetstr("us", NULL), 0, ft_put);
	// if (ed->rpz[3] == 1)
	// 	tputs(tgetstr("so", NULL), 0, ft_put);
	ft_putchar(ed->c[0]);
	// tputs(tgetstr("se", NULL), 0, ft_put);
	// tputs(tgetstr("ue", NULL), 0, ft_put);
}

void    print_shell(t_edit *ed)
{
	int			i;
	
	i = -1;
    init_cursor(ed);
	tputs(tgetstr("cd", NULL), 0, ft_put);
	ft_putstr(">>");
	while (ed->rpz[0] == 0)
		ed = ed->next;
	while (ed->rpz[1] == 0)
	{
		my_tputs(ed);
		ed = ed->next;
	}
	put_cursor(ed);
}


void	put_cursor(t_edit *ed)
{
    tputs(tgetstr("rc", NULL), 0, ft_put);
    while (ed->rpz[2] == 0)
        ed = ed->next;
    if (ed->rpz[2] % g_nb->tb[0] != 0 && ed->rpz[2] / g_nb->tb[0] > 0)
        ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(ed->rpz[2] / g_nb->tb[0]),"B")));
	ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((ed->rpz[2] - 1) % g_nb->tb[0]), "C")));

}

void    init_cursor(t_edit *ed)
{
    while (ed->rpz[2] == 0)
        ed = ed->next;
    give_max();
    // max len et non cursor
    if (ed->rpz[2] % g_nb->tb[0] != 0 && (ed->rpz[2]) / g_nb->tb[0] > 0)
        ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((ed->rpz[2] / g_nb->tb[0])), "A")));
    ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(ed->rpz[2] % g_nb->tb[0]),"D")));	
    tputs(tgetstr("sc", NULL), 0, ft_put);
    // sleep(1);    
}