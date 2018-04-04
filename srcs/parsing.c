/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:09:16 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 10:47:39 by ltran            ###   ########.fr       */
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

int		parsing_op(char *s, t_cmd **ex, t_env *env, t_froz *fz)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == ' ')
		++i;
	s = quote_variable(s, NULL, env);
	*ex = separate_cmd(s, i, i, *ex);
	i = parse_type(ex);
	*ex = parse_op_int(*ex, s);
	if ((i = parse_synthaxe(*ex)) != 0)
	{
		free(s);
		return (i);
	}
	join_redirecting(ex);
	join_ex(ex);
	free(s);
	return (add_delim(fz, *ex));
}

int		parsing_quote(char *s)
{
	int		i;
	int		a;

	i = 0;
	a = -1;
	while (s[++a])
	{
		if (s[a] == '"' && i != 1)
			i = (i == 0) ? 2 : 0;
		else if (s[a] == 39 && i != 2)
			i = (i == 0) ? 1 : 0;
	}
	return (i);
}

int		parsing(t_edit *ed, t_froz *fz, t_cmd **ex, t_env *env)
{
	*ex = init_ex(NULL);
	if (fz->mode[3] == 6)
		add_doc(fz, ed_str(ed, NULL, fz->nb[0] - giv_last(fz)));
	else
		fz->cmd = join_cmd_nw(fz->cmd, ed, fz);
	while (ed->rpz[0] == 0)
		ed = ed->next;
	if ((fz->mode[3] = parsing_quote(fz->cmd)))
	{
		free_all_ex(ex);
		return (0);
	}
	else if ((fz->mode[3] = parsing_op(ft_strdup(fz->cmd), ex, env, fz)))
	{
		free_all_ex(&(*ex));
		if (!(fz->mode[3] >= 0 && fz->mode[3] <= 6))
			return (error_syntax(fz));
	}
	else if (fz->mode[3] == 0)
		return (1);
	return (0);
}
