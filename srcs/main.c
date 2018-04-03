/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:55:03 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 12:56:09 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		main(void)
{
	t_env	*env;

	env = NULL;
	g_nb = init_shell(&fz, &env, &ed, &hs);
	while (42)
	{
		ls_signal(fz->mode[3]);
		read(0, &fz->buf, 4);
		if (fz->buf[0] == 10)
		{
			cursor_end(ed);
			env = treat_cmd(env, &ed, &hs, &fz);
			init_for_new(&hs, &fz, &ed);
		}
		else if (fz->buf[0] == 3)
		{
			write(1, "\n", 1);
			init_for_new(&hs, &fz, &ed);
		}
		else if (fz->buf[0] == 0 && fz->buf[1] == 0 && fz->buf[2] == 0)
			free_for_exit();
		else
			ed = touch(&ed, &fz, &hs);
		init_data(&fz);
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
