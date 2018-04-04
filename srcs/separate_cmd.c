/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:15:11 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:16:21 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	sub_into_ex_fct(char *s, int i, int in, t_cmd *ex)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(s, in, i - in);
	in = in + white_space(tmp);
	if (tmp)
		free(tmp);
	ex->cmd = ft_strsub(s, in, i - in);
	ex->start = in;
}

t_cmd	*sub_into_ex(char *s, int i, int in, t_cmd *ex)
{
	t_cmd	*nw;

	nw = NULL;
	if (i == in)
		return (ex);
	if (ex->cmd == NULL && ex->prev && ex->next && ex->prev->type == 42
		&& ex->next->type == 42)
		sub_into_ex_fct(s, i, in, ex);
	else
	{
		while (ex->next != NULL)
			ex = ex->next;
		if (!(nw = (t_cmd*)malloc(sizeof(t_cmd))))
			return (NULL);
		sub_into_ex_fct(s, i, in, nw);
		ex->prev->next = nw;
		nw->next = ex;
		nw->prev = ex->prev;
		ex->prev = nw;
	}
	return (ex);
}

t_cmd	*separate_cmd_fct(char *s, int *i, int *in, t_cmd *ex)
{
	while (!(s[*i] != '&' && s[*i] != '|' && s[*i] != ';' && s[*i] != '>'
		&& s[*i] != '<') && s[*i])
		++(*i);
	ex = sub_into_ex(s, *i, *in, ex);
	*in = *i;
	return (ex);
}

t_cmd	*separate_cmd(char *s, int i, int in, t_cmd *ex)
{
	int		q;

	q = 0;
	if (!(s[i] != '&' && s[i] != '|' && s[i] != ';' && s[i] != '>'
		&& s[i] != '<') && s[i])
		ex = separate_cmd_fct(s, &i, &in, ex);
	while (s[i])
	{
		while ((s[i] && (s[i] != '&' && s[i] != '|' && s[i] != ';' &&
			s[i] != ' ' && s[i] != '>' && s[i] != '<')) || (s[i] && q != 0))
		{
			if (s[i] == 39 && q != 2)
				q = (q == 0) ? 1 : 0;
			else if (s[i] == '"' && q != 1)
				q = (q == 0) ? 2 : 0;
			++i;
		}
		ex = sub_into_ex(s, i, in, ex);
		in = i;
		while (s[i] == ' ')
			++i;
		in = i;
		ex = separate_cmd_fct(s, &i, &in, ex);
	}
	return (ex);
}
