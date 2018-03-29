/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:23:49 by ltran             #+#    #+#             */
/*   Updated: 2018/03/29 18:29:58 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void    ctrl_touch(t_edit **ed, t_froz **fz, char c, t_his *hs)
{
	while ((*ed)->rpz[2] == 0) /// INIT jusqua curseur
		*ed = (*ed)->next;
	if (c == 20 || c == 14)
		ctrl_de_test(*ed, *fz, c , hs);
	else if (c == 5 || c == 23)
		*ed = move_word(*ed, c);
	else if (c == 11 || c == 12)
		*ed = up_down(*ed, c);
	else if (c == 2) //copier B
		*ed = copy(*ed, &(*fz));
	else if (c == 24) //couper X
		cut(&(*ed), &(*fz));
	else if (c == 1) //coller A
		*ed = paste(*ed, &(*fz));
}

t_edit  *home_end(t_edit *ed, t_froz *fz)
{
	int     i;

	if (fz->buf[2] == 72)
	{
		ed->rpz[2] = 0;
		while (ed->rpz[0] == 0)
			ed = ed->next;
		ed->rpz[2] = giv_last(fz);    
	}
	else if (fz->buf[2] == 70 && ed->rpz[1] == 0) //ctrl l
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
	return(ed);
}

/// a change up and down rpz[2] to rpz[3]

t_edit  *up_down(t_edit *ed, char c)
{
	int     cur;
	
	cur = ed->rpz[3];
	ed->rpz[2] = 0;
	if (c == 11) //ctrl a
	{
		while (ed->rpz[1] != 1 && ed->rpz[3] < cur + g_nb->tb[0] && ed->next->rpz[3] < cur + g_nb->tb[0] + 1)
			ed = ed->next;
		ed->rpz[2] = ed->rpz[3];
	}
	else if (c == 12) //ctrl q
	{
		while (ed->rpz[0] == 0 && ed->prev->rpz[3] > cur - g_nb->tb[0] - 1)
			ed = ed->prev;
		ed->rpz[2] = ed->rpz[3];
	}
	return (ed);
}

t_edit  *move_word(t_edit *ed, char c)
{
	int i;

	if (c == 5 && ed->rpz[1] == 0) //ctrl e
	{
		i = ed->rpz[2];
		ed->rpz[2] = 0;
		if (ed->c[0] == '\n')
			ed = ed->next;
		while(ed->c[0] == ' ' && ed->rpz[1] == 0 && ++i)
			ed = ed->next;
		while(ed->c[0] != ' ' && ed->c[0] != '\n' && ed->rpz[1] == 0 && ++i)
			ed = ed->next;
		ed->rpz[2] = i;
	}
	else if (c == 23 && ed->rpz[0] == 0)//ctrl w
	{
		i = ed->rpz[2];
		ed->rpz[2] = 0;
		if ((ed->c[0] == ' ' || ed->c[0] == '\n') && --i)
			ed = ed->prev;
		while(ed->c[0] != ' ' && ed->c[0] != '\n' && ed->rpz[0] == 0 && --i)
			ed = ed->prev;
		if (ed->c[0] == '\n')
		{
			ed->rpz[2] = i;
			return (ed);
		}
		while(ed->c[0] == ' ' && ed->rpz[0] == 0 && --i)
			ed = ed->prev;
		if (ed->rpz[0] == 0)
			ed->next->rpz[2] = i +1;
		else
			ed->rpz[2] = i;
		
	}
	return (ed);
}

void    ctrl_de_test(t_edit *ed, t_froz *fz, char c, t_his *hs)
{
	if (fz)
		;
	/* ctrl T Lire ed avec rpz
	*/
	if (c == 20)
	{
		while (ed->rpz[0] == 0)
		{
			printf("ss\n");
			ed = ed->next;
		}
		while (ed->rpz[1] == 0)
		{
			printf("%c [%i][%i][%i][%i][%i]\n", ed->c[0], ed->rpz[0], ed->rpz[1], ed->rpz[2], ed->rpz[3], ed->rpz[4]);
			ed = ed->next;
		}
		printf("%c [%i][%i][%i][%i]\nnb = %i co[%i] | li[%i]\n", ed->c[0], ed->rpz[0], ed->rpz[1], ed->rpz[2], ed->rpz[3], fz->nb[0], g_nb->tb[0], g_nb->tb[1]);
	}
	else if (c == 14)// ctrl n
	{
		if (!hs)
			return ;
		while (hs && hs->next != NULL)
		{
			printf("->%s\n", hs->cmd);
			hs = hs->next;
		}
		printf("->%s\n", hs->cmd);
	}
	sleep(3);
}
