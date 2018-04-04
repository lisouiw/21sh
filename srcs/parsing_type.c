/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:58:46 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 16:28:31 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_cmd	*giv_type(t_cmd *ex, char *s)
{
	if (ex->cmd[0] == '|')
		ex = parse_pipe_or(ex);
	else if (ex->cmd[0] == '&')
		ex = parse_ampersand(ex);
	else if (ex->cmd[0] == '<')
		ex = parse_less_than(ex, s);
	else if (ex->cmd[0] == '>')
		ex = parse_great_than(ex, s);
	else if (ex->cmd[0] == ';')
		ex->type = ft_strcmp(ex->cmd, ";") == 0 ? 13 : -1;
	else if (if_only(ex->cmd, '\n') == 1)
		ex->type = 14;
	return (ex);
}

t_cmd	*parse_op_int(t_cmd *ex, char *s)
{
	while (ex->next != NULL)
	{
		if (ex->type == 1)
			ex = giv_type(ex, s);
		ex = ex->next;
	}
	while (ex->prev != NULL)
		ex = ex->prev;
	return (ex);
}

int		parse_type(t_cmd **ex)
{
	char	c;

	while ((*ex)->prev->cmd != NULL)
		*ex = (*ex)->prev;
	while ((*ex)->cmd != NULL)
	{
		c = (*ex)->cmd[0];
		if (c == '&' || c == '|' || c == ';' || c == '>' || c == '<' ||
			if_only((*ex)->cmd, '\n') == 1)
			(*ex)->type = 1;
		else
			(*ex)->type = 0;
		*ex = (*ex)->next;
	}
	while ((*ex)->prev != NULL)
		*ex = (*ex)->prev;
	return (0);
}
