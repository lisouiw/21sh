/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:25:59 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:26:18 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	init_data(t_froz **fz)
{
	(*fz)->buf[0] = 0;
	(*fz)->buf[1] = 0;
	(*fz)->buf[2] = 0;
}

void	init_for_new(t_his **hs, t_froz **fz, t_edit **ed)
{
	int		status;

	wait(&status);
	set_up_term();
	wait(0);
	tputs(tgetstr("sc", NULL), 0, ft_put);
	wait(0);
	put_prompt_init(&(*fz));
	free_ed(&(*ed), *fz);
	(*ed)->rpz[2] = giv_last(*fz);
	(*ed)->rpz[3] = giv_last(*fz);
	free_init_fz(*fz);
	if (*hs == NULL)
		return ;
	while ((*hs)->prev != NULL)
		*hs = (*hs)->prev;
	wait(0);
}

t_cmd	*init_ex(t_cmd *ex)
{
	if (!(ex = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	ex->cmd = NULL;
	ex->type = 0;
	if (!(ex->prev = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	ex->prev->cmd = NULL;
	ex->prev->prev = NULL;
	ex->prev->type = 42;
	ex->prev->start = 0;
	ex->prev->next = ex;
	if (!(ex->next = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	ex->next->cmd = NULL;
	ex->next->next = NULL;
	ex->next->prev = ex;
	ex->next->type = 42;
	ex->next->start = 0;
	return (ex);
}

void	init_launch(t_exec *dot, t_cmd **ex)
{
	while ((*ex)->prev != NULL)
		*ex = (*ex)->prev;
	*ex = (*ex)->next;
	dot->cmd = 0;
	dot->out = 1;
	dot->in = 0;
	dot->ok = 0;
}
