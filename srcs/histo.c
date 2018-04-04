/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:14:32 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 16:14:48 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	histo_add(t_his *hs, t_edit **ed, t_froz **fz)
{
	int		i;

	i = -1;
	while (hs->cmd[++i])
		*ed = add_ed(*ed, hs->cmd[i], NULL, &(*fz));
	*ed = giv_position(*ed, giv_last(*fz));
	(*fz)->nb[0] = i + giv_last(*fz);
}

t_his	*histo(t_his *hs, char c, t_edit **ed, t_froz **fz)
{
	free_ed(&(*ed), *fz);
	if (c == 65 && hs->next != NULL)
	{
		hs = hs->next;
		if (hs->cmd == NULL)
		{
			(*fz)->nb[0] = giv_last(*fz);
			return (hs);
		}
		histo_add(hs, ed, fz);
	}
	else if (c == 66 && hs->prev != NULL)
	{
		hs = hs->prev;
		if (hs->cmd == NULL)
		{
			(*fz)->nb[0] = giv_last(*fz);
			return (hs);
		}
		histo_add(hs, ed, fz);
	}
	return (hs);
}
