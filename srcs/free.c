/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:01:58 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 17:17:06 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	free_all_ex(t_cmd **ex)
{
	t_cmd	*tmp;

	while ((*ex)->next != NULL)
		*ex = (*ex)->next;
	while ((*ex)->prev != NULL)
	{
		tmp = (*ex)->prev;
		free((*ex)->cmd);
		free(*ex);
		*ex = tmp;
	}
	free((*ex)->cmd);
	free(*ex);
}

void	free_init_fz(t_froz *fz)
{
	fz->mode[0] = 0;
	fz->mode[1] = 0;
	fz->mode[2] = 1;
	if (fz->mode[3] == 0)
	{
		free(fz->cmd);
		fz->cmd = NULL;
		while (fz->here->prev != NULL)
			fz->here = fz->here->prev;
		while (fz->here->next != NULL)
		{
			if (fz->here->delim)
				free(fz->here->delim);
			if (fz->here->doc)
				free(fz->here->doc);
			fz->here = fz->here->next;
			free(fz->here->prev);
			fz->here->prev = NULL;
		}
		fz->here->ok[0] = 0;
		fz->here->doc = NULL;
		fz->here->delim = NULL;
	}
}

void	free_for_hs(void)
{
	while (g_hs->prev != NULL)
		g_hs = g_hs->prev;
	while (g_hs->next != NULL)
	{
		free(g_hs->cmd);
		g_hs = g_hs->next;
		free(g_hs->prev);
	}
	free(g_hs);
}

void	free_for_exit(void)
{
	free_for_hs();
	if (g_fz->cmd)
		free(g_fz->cmd);
	if (g_fz->paste)
		free(g_fz->paste);
	while (g_fz->here->prev != NULL)
		g_fz->here = g_fz->here->prev;
	while (g_fz->here->next != NULL)
	{
		if (g_fz->here->delim)
			free(g_fz->here->delim);
		if (g_fz->here->doc)
			free(g_fz->here->doc);
		g_fz->here = g_fz->here->next;
		free(g_fz->here->prev);
		g_fz->here->prev = NULL;
	}
	free(g_fz->here);
	free(g_fz);
	exit(-1);
}

void	free_elem(t_env *tmp)
{
	ft_strdel(&tmp->name);
	ft_strdel(&tmp->ctn);
	free(tmp);
}
