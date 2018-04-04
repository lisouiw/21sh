/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pascutcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:15:05 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 16:12:46 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_edit	*paste(t_edit *ed, t_froz **fz)
{
	int	i;

	i = -1;
	while (ed->rpz[2] == 0)
		ed = ed->next;
	while ((*fz)->paste[++i])
		ed = add_ed(ed, (*fz)->paste[i], NULL, &(*fz));
	return (ed);
}

t_edit	*copy(t_edit *ed, t_froz **fz)
{
	if ((*fz)->mode[0] == 1)
	{
		if ((*fz)->paste != NULL)
			free((*fz)->paste);
		(*fz)->paste = keep_paste(&ed, NULL);
	}
	(*fz)->mode[0] = ((*fz)->mode[0] == 0) ? 1 : 0;
	if ((*fz)->mode[1] == 1 || (*fz)->mode[0] == 0)
	{
		while (ed->rpz[0] == 0)
			ed = ed->next;
		while (ed->rpz[1] == 0)
		{
			ed->rpz[4] = 0;
			ed = ed->next;
		}
		ed->rpz[4] = 0;
		while (ed->rpz[2] == 0)
			ed = ed->next;
	}
	else
		ed->rpz[4] = 1;
	return (ed);
}

void	cut(t_edit **ed, t_froz **fz)
{
	if ((*fz)->mode[1] == 1)
	{
		if ((*fz)->paste != NULL)
			free((*fz)->paste);
		(*fz)->paste = keep_paste(&(*ed), NULL);
		free_cut(&(*ed), *fz);
	}
	(*fz)->mode[1] = ((*fz)->mode[1] == 0) ? 1 : 0;
	if ((*fz)->mode[0] == 1 || (*fz)->mode[1] == 0)
	{
		while ((*ed)->rpz[0] == 0)
			*ed = (*ed)->next;
		while ((*ed)->rpz[1] == 0)
		{
			(*ed)->rpz[4] = 0;
			*ed = (*ed)->next;
		}
		(*ed)->rpz[4] = 0;
		while ((*ed)->rpz[2] == 0)
			*ed = (*ed)->next;
	}
	else
		(*ed)->rpz[4] = 1;
}

int		give_paste_in(t_edit **ed)
{
	int		i;

	i = 0;
	while ((*ed)->rpz[0] == 0)
		*ed = (*ed)->next;
	while ((*ed)->rpz[4] == 0)
		*ed = (*ed)->next;
	while ((*ed)->rpz[4] == 1 && (*ed)->rpz[1] == 0)
	{
		++i;
		*ed = (*ed)->next;
	}
	return (i);
}

char	*keep_paste(t_edit **ed, char *s)
{
	int		i;
	int		a;

	a = -1;
	i = give_paste_in(ed);
	while ((*ed)->rpz[0] == 0)
		*ed = (*ed)->next;
	while ((*ed)->rpz[4] == 0)
		*ed = (*ed)->next;
	if (!(s = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	while (++a < i)
	{
		s[a] = (*ed)->c[0];
		*ed = (*ed)->next;
	}
	s[a] = '\0';
	return (s);
}
