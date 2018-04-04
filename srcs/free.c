/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:01:58 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:22:42 by ltran            ###   ########.fr       */
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
	while (hs->prev != NULL)
		hs = hs->prev;
	while (hs->next != NULL)
	{
		free(hs->cmd);
		hs = hs->next;
		free(hs->prev);
	}
	free(hs);
}

void	free_for_exit(void)
{
	free_for_hs();
	if (fz->cmd)
		free(fz->cmd);
	if (fz->paste)
		free(fz->paste);
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
	free(fz->here);
	free(fz);
	exit(-1);
}

void	free_elem(t_env *tmp)
{
	ft_strdel(&tmp->name);
	ft_strdel(&tmp->ctn);
	free(tmp);
}
