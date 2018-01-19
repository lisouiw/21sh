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

void    print_shell(t_edit *ed, t_froz *fz)
{
	int			i;
	
	i = 3;
    tputs(tgetstr("rc", NULL), 0, ft_put);
	tputs(tgetstr("cd", NULL), 0, ft_put);
	ft_putstr("\033[0;33;40m>>\033[0m");
	while (ed->rpz[0] == 0)
		ed = ed->next;
	while (ed->rpz[1] == 0)
	{
		my_tputs(ed);
		if (++i % g_nb->tb[0] == 1)
			ft_putchar('\n');
		ed = ed->next;
	}
	save_init(fz);
	put_cursor(ed);
}

void	put_cursor(t_edit *ed)
{
	int		div;

    while (ed->rpz[2] == 0)
		ed = ed->next;
	div = ed->rpz[2] / g_nb->tb[0];
    if (ed->rpz[2] > g_nb->tb[0] && ed->rpz[2] % g_nb->tb[0] != 0)
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(div),"B")));
	else if (ed->rpz[2] > g_nb->tb[0] && ed->rpz[2] % g_nb->tb[0] == 0)
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(div - 1),"B")));
	if (ed->rpz[2] % g_nb->tb[0] != 1)
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((ed->rpz[2] - 1) % g_nb->tb[0]), "C")));
}

void	save_init(t_froz *fz)
{
	int		i;

	i = fz->nb[0];
	ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(g_nb->tb[0]), "D")));
	if (i > g_nb->tb[0] && i % g_nb->tb[0] == 0)
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((i / g_nb->tb[0]) - 1),"A")));
	else if (i > (g_nb->tb[0]))
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((i / g_nb->tb[0])),"A")));
	tputs(tgetstr("sc", NULL), 0, ft_put);
}