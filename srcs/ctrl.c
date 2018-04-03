/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:23:49 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 22:21:27 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	ctrl_touch(t_edit **ed, t_froz **fz, char c)
{
	while ((*ed)->rpz[2] == 0)
		*ed = (*ed)->next;
	if (c == 5 && (*ed)->rpz[1] == 0)
		*ed = move_word_right(*ed);
	else if (c == 23 && (*ed)->rpz[0] == 0)
		*ed = move_word_left(*ed);
	else if (c == 11 || c == 12)
		*ed = up_down(*ed, c);
	else if (c == 2)
		*ed = copy(*ed, &(*fz));
	else if (c == 24)
		cut(&(*ed), &(*fz));
	else if (c == 1 && (*fz)->paste != NULL)
		*ed = paste(*ed, &(*fz));
}

t_edit	*home_end(t_edit *ed, t_froz *fz)
{
	int		i;

	if (fz->buf[2] == 72)
	{
		ed->rpz[2] = 0;
		while (ed->rpz[0] == 0)
			ed = ed->next;
		ed->rpz[2] = giv_last(fz);
	}
	else if (fz->buf[2] == 70 && ed->rpz[1] == 0)
	{
		i = ed->rpz[2];
		ed->rpz[2] = 0;
		while (ed->rpz[1] == 0)
		{
			ed = ed->next;
			++i;
		}
		ed->rpz[2] = i;
	}
	return (ed);
}

t_edit	*up_down(t_edit *ed, char c)
{
	int		cur;

	cur = ed->rpz[3];
	ed->rpz[2] = 0;
	if (c == 11)
	{
		while (ed->rpz[1] != 1 && ed->rpz[3] < cur + g_nb->tb[0] &&
			ed->next->rpz[3] < cur + g_nb->tb[0] + 1)
			ed = ed->next;
		ed->rpz[2] = ed->rpz[3];
	}
	else if (c == 12)
	{
		while (ed->rpz[0] == 0 && ed->prev->rpz[3] > cur - g_nb->tb[0] - 1)
			ed = ed->prev;
		ed->rpz[2] = ed->rpz[3];
	}
	return (ed);
}

t_edit	*move_word_right(t_edit *ed)
{
	int i;

	i = ed->rpz[2];
	ed->rpz[2] = 0;
	if (ed->c[0] == '\n')
		ed = ed->next;
	while (ed->c[0] == ' ' && ed->rpz[1] == 0 && ++i)
		ed = ed->next;
	while (ed->c[0] != ' ' && ed->c[0] != '\n' && ed->rpz[1] == 0 && ++i)
		ed = ed->next;
	ed->rpz[2] = i;
	return (ed);
}

t_edit	*move_word_left(t_edit *ed)
{
	int	i;

	i = ed->rpz[2];
	ed->rpz[2] = 0;
	if ((ed->c[0] == ' ' || ed->c[0] == '\n') && --i)
		ed = ed->prev;
	while (ed->c[0] != ' ' && ed->c[0] != '\n' && ed->rpz[0] == 0 && --i)
		ed = ed->prev;
	if (ed->c[0] == '\n')
	{
		ed->rpz[2] = i;
		return (ed);
	}
	while (ed->c[0] == ' ' && ed->rpz[0] == 0 && --i)
		ed = ed->prev;
	if (ed->rpz[0] == 0)
		ed->next->rpz[2] = i + 1;
	else
		ed->rpz[2] = i;
	return (ed);
}
