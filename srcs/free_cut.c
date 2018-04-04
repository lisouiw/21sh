/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:10:58 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 16:11:15 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	free_cut1(t_edit **ed, t_edit *tmp)
{
	while ((*ed)->rpz[0] == 0)
		*ed = (*ed)->next;
	while ((*ed)->rpz[4] == 0)
		*ed = (*ed)->next;
	while ((*ed)->rpz[4] == 1 && (*ed)->rpz[1] == 0)
	{
		tmp = *ed;
		(*ed)->prev->next = (*ed)->next;
		(*ed)->next->prev = (*ed)->prev;
		(*ed)->next->rpz[0] = (*ed)->rpz[0];
		free(tmp);
		*ed = (*ed)->next;
	}
	(*ed)->rpz[2] = (*ed)->rpz[3];
	while ((*ed)->rpz[0] == 0)
		*ed = (*ed)->next;
}

void	free_cut(t_edit **ed, t_froz *fz)
{
	t_edit	*tmp;

	tmp = NULL;
	free_cut1(ed, tmp);
	(*ed)->rpz[3] = giv_last(fz);
	while ((*ed)->rpz[1] == 0)
	{
		while ((*ed)->rpz[1] == 0)
		{
			(*ed) = (*ed)->next;
			if ((*ed)->prev->c[0] == '\n' && tmp->prev->rpz[3] %
				g_nb->tb[0] != 0)
				(*ed)->rpz[3] = ((((*ed)->prev->rpz[3] / g_nb->tb[0]) + 1)
					* g_nb->tb[0]) + 1;
			else
				(*ed)->rpz[3] = (*ed)->prev->rpz[3] + 1;
		}
		if ((*ed)->prev->c[0] == '\n' && (*ed)->prev->rpz[3] %
			g_nb->tb[0] != 0)
			(*ed)->rpz[3] = ((((*ed)->prev->rpz[3] / g_nb->tb[0]) + 1)
				* g_nb->tb[0]) + 1;
	}
}
