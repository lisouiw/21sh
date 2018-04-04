/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:29:00 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:30:52 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	join_ex(t_cmd **ex)
{
	char	*tmp;
	char	*tmp2;
	t_cmd	*cmd;

	while ((*ex)->prev != NULL)
		*ex = (*ex)->prev;
	while ((*ex)->next != NULL)
	{
		if ((*ex)->type == 0 && (*ex)->next->type == 0)
		{
			cmd = (*ex)->next;
			tmp = ft_strjoin(" ", (*ex)->next->cmd);
			tmp2 = ft_strjoin((*ex)->cmd, tmp);
			free((*ex)->cmd);
			(*ex)->cmd = tmp2;
			(*ex)->next = (*ex)->next->next;
			(*ex)->next->prev = *ex;
			free(tmp);
			free(cmd->cmd);
			free(cmd);
		}
		else
			*ex = (*ex)->next;
	}
}

void	join_redirecting2(t_cmd **join, t_cmd **ex)
{
	char	*tmp;
	char	*tmp2;
	t_cmd	*cmd;

	while ((*ex)->type >= 6 && (*ex)->type <= 11)
	{
		*ex = (*ex)->next;
		if ((*ex)->type == 0)
		{
			tmp = ft_strjoin((*join)->cmd, " ");
			tmp2 = ft_strjoin(tmp, (*ex)->cmd);
			free((*join)->cmd);
			(*join)->cmd = tmp2;
			cmd = *ex;
			*ex = (*ex)->next;
			(*ex)->prev = (*ex)->prev->prev;
			(*ex)->prev->next = (*ex);
			free(tmp);
			free(cmd->cmd);
			free(cmd);
		}
	}
}

void	join_redirecting(t_cmd **ex)
{
	while ((*ex)->prev != NULL)
		*ex = (*ex)->prev;
	while ((*ex)->next != NULL)
	{
		while ((*ex)->next != NULL)
		{
			if ((*ex)->type >= 6 && (*ex)->type <= 11)
				join_redirecting2(&(*ex)->prev, ex);
			if ((*ex)->next != NULL)
				*ex = (*ex)->next;
		}
	}
}
