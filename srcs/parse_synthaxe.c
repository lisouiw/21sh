/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_synthaxe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:00:08 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 16:04:51 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		parse_synthaxe_1(t_cmd *ex)
{
	int		i;

	while (ex->prev != NULL)
		ex = ex->prev;
	ex = ex->next;
	i = ex->type;
	if (i == 3 | i == 4 || i == 5 || i == 13)
		return (-ex->type);
	else if (i < 0)
		return (ex->type);
	return (0);
}

void	parse_synthaxe_2(t_cmd *ex)
{
	t_cmd	*tmp;

	while (ex->prev != NULL)
		ex = ex->prev;
	ex = ex->next;
	while (ex->next != NULL)
	{
		if (ex->type >= 6 && ex->type <= 11 && ex->next->type == 0)
		{
			tmp = ex->next;
			ex->next->next->prev = ex;
			ex->next = ex->next->next;
			free(tmp->cmd);
			free(tmp);
		}
		ex = ex->next;
	}
}

int		parse_synthaxe(t_cmd *ex)
{
	int		i;

	if ((i = parse_synthaxe_1(ex)) < 0)
		return (i);
	while (ex->next != NULL)
	{
		if (ex->type >= 3 && ex->type <= 5 && ex->prev->type == 0
			&& ex->next->type == 42)
			return (ex->type);
		else if (ex->type >= 3 && ex->type <= 5 && ex->prev->type != 0
			&& ex->next->type != 0)
			return (-ex->type);
		else if (ex->type >= 6 && ex->type <= 11 && ex->next->type != 0)
			return (-ex->type);
		else if (ex->type == 13 && ((ex->prev->type >= 3 && ex->prev->type <= 5)
			|| ex->prev->type == 13))
			return (-ex->type);
		else if (ex->type < 0)
			return (ex->type);
		ex = ex->next;
	}
	parse_synthaxe_2(ex);
	return (0);
}
