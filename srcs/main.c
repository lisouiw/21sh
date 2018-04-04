/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:55:03 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 17:17:04 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		main(void)
{
	g_env = NULL;
	g_nb = init_shell(&g_fz, &g_env, &g_ed, &g_hs);
	while (42)
	{
		ls_signal(g_fz->mode[3]);
		read(0, &g_fz->buf, 4);
		if (g_fz->buf[0] == 10)
		{
			cursor_end(g_ed);
			g_env = treat_cmd(g_env, &g_ed, &g_hs, &g_fz);
			init_for_new(&g_hs, &g_fz, &g_ed);
		}
		else if (g_fz->buf[0] == 3)
		{
			g_fz->mode[3] = 0;
			add_his(&g_hs, NULL, g_fz);
			write(1, "\n", 1);
			init_for_new(&g_hs, &g_fz, &g_ed);
		}
		else if (g_fz->buf[0] == 0 && g_fz->buf[1] == 0 && g_fz->buf[2] == 0)
			free_for_exit();
		else
			g_ed = touch(&g_ed, &g_fz, &g_hs);
		init_data(&g_fz);
	}
}

void	cursor_end(t_edit *ed)
{
	int		i;

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

void	put_my_cur(int nb, char c)
{
	char	*i;

	i = ft_itoa(nb);
	ft_putstr("\033[");
	ft_putstr(i);
	ft_putchar(c);
	free(i);
}
