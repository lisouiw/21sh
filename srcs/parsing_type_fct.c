/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type_fct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:58:19 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 22:21:44 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_cmd	*parse_redirec(t_cmd *ex, char *s)
{
	char	*tmp2;
	t_cmd	*tmp;

	if (ex->prev->cmd != NULL && ex->prev != NULL && isnumber(ex->prev->cmd)
		&& s[ex->start - 1] != ' ')
	{
		tmp = ex->prev;
		tmp2 = strjoin_free_n(ex->prev->cmd,
			strjoin_free_n(" ", ex->cmd, 2), 3);
		ex->cmd = tmp2;
		ex->prev->prev->next = ex;
		ex->prev = ex->prev->prev;
		free(tmp);
	}
	if (ex->next != NULL && ex->next->type != 42 && ex->next->type == 0)
	{
		tmp2 = strjoin_free_n(ex->cmd, ft_strjoin(" ", ex->next->cmd), 3);
		ex->cmd = tmp2;
	}
	return (ex);
}

t_cmd	*parse_ampersand(t_cmd *ex)
{
	if (ft_strcmp(ex->cmd, "&&") == 0)
		ex->type = 4;
	else if (ft_strcmp(ex->cmd, "&") == 0)
		ex->type = -20;
	else if (ft_strcmp(ex->cmd, "&<") == 0 || ft_strcmp(ex->cmd, "&>") == 0)
		ex->type = -1;
	else
		ex->type = -1;
	return (ex);
}

t_cmd	*parse_great_than(t_cmd *ex, char *s)
{
	if (ft_strcmp(ex->cmd, ">") == 0)
	{
		ex->type = 8;
		ex = parse_redirec(ex, s);
	}
	else if (ft_strcmp(ex->cmd, ">>") == 0)
	{
		ex->type = 9;
		ex = parse_redirec(ex, s);
	}
	else if (ft_strcmp(ex->cmd, ">&") == 0)
	{
		ex->type = 10;
		ex = parse_redirec(ex, s);
	}
	else
		ex->type = -1;
	return (ex);
}

t_cmd	*parse_less_than(t_cmd *ex, char *s)
{
	if (ft_strcmp(ex->cmd, "<") == 0)
	{
		ex->type = 7;
		ex = parse_redirec(ex, s);
	}
	else if (ft_strcmp(ex->cmd, "<<") == 0)
	{
		ex->type = 6;
		ex = parse_redirec(ex, s);
	}
	else if (ft_strcmp(ex->cmd, "<&") == 0)
	{
		ex->type = 11;
		ex = parse_redirec(ex, s);
	}
	else
		ex->type = -1;
	return (ex);
}

t_cmd	*parse_pipe_or(t_cmd *ex)
{
	if (ft_strcmp(ex->cmd, "|") == 0)
		ex->type = 3;
	else if (ft_strcmp(ex->cmd, "||") == 0)
		ex->type = 5;
	else
		ex->type = -1;
	return (ex);
}
