/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:49:37 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:26:59 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_his	*init_hs(t_his *hs, t_his *next)
{
	if (!(hs = (t_his*)malloc(sizeof(t_his))))
		return (NULL);
	if (!(next = (t_his*)malloc(sizeof(t_his))))
		return (NULL);
	hs->cmd = NULL;
	next->cmd = NULL;
	next->prev = hs;
	next->next = NULL;
	hs->next = next;
	hs->prev = NULL;
	return (hs);
}

t_num	*init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs)
{
	struct ttysize	ts;

	if ((*env = give_env(NULL)) == NULL)
	{
		ft_putstr_fd("Need An Environment\n", 2);
		exit(0);
	}
	set_up_term();
	tputs(tgetstr("cl", NULL), 0, ft_put);
	*ed = init_edit(NULL);
	*hs = init_hs(NULL, NULL);
	*fz = init_fz(NULL);
	tputs(tgetstr("sc", NULL), 0, ft_put);
	ft_putstr("\033[0;33;40m>>\033[0m");
	if (!(g_nb = (t_num*)malloc(sizeof(t_num))))
		return (NULL);
	ioctl(1, TIOCGSIZE, &ts);
	g_nb->tb[0] = ts.ts_cols;
	g_nb->tb[1] = ts.ts_lines;
	return (g_nb);
}

t_froz	*init_fz(t_froz *fz)
{
	if (!(fz = (t_froz*)malloc(sizeof(t_froz))))
		return (NULL);
	fz->buf[0] = 0;
	fz->buf[1] = 0;
	fz->buf[2] = 0;
	fz->mode[0] = 0;
	fz->mode[1] = 0;
	fz->mode[2] = 1;
	fz->mode[3] = 0;
	fz->nb[0] = 3;
	fz->paste = NULL;
	fz->cmd = NULL;
	if (!(fz->here = (t_here*)malloc(sizeof(t_here))))
		return (NULL);
	fz->here->next = NULL;
	fz->here->prev = NULL;
	fz->here->delim = NULL;
	fz->here->ok[0] = 0;
	return (fz);
}
