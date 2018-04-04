/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:46:25 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 16:15:38 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	malloc_here(t_froz *fz)
{
	if (!(fz->here->next = (t_here*)malloc(sizeof(t_here))))
		return ;
	fz->here->next->prev = fz->here;
	fz->here = fz->here->next;
	fz->here->delim = NULL;
	fz->here->next = NULL;
}

void	add_here_struct(t_froz *fz, char *s)
{
	char	**t;

	t = ft_strsplit(s, ' ');
	if ((!fz->here->delim) && fz->here->prev == NULL && fz->here->next == NULL)
	{
		fz->here->delim = ft_strdup(t[1]);
		fz->here->doc = NULL;
		fz->here->ok[0] = 0;
		fz->here->prev = NULL;
		malloc_here(fz);
	}
	else if (fz->here->delim == NULL)
	{
		fz->here->delim = ft_strdup(t[1]);
		fz->here->doc = NULL;
		fz->here->ok[0] = 0;
		malloc_here(fz);
	}
	else
		fz->here = fz->here->next;
	free_tab(t);
}

int		check_struct(t_froz *fz)
{
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	while (fz->here->delim != NULL && fz->here->ok[0] == 1)
		fz->here = fz->here->next;
	if (fz->here->delim == NULL && fz->here->next == NULL)
		fz->mode[3] = 0;
	else
		fz->mode[3] = 6;
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	return (fz->mode[3]);
}
