/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatmt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:36:32 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 13:20:25 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_env	*treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
	t_cmd	*ex;

	ex = NULL;
	while ((*cmd)->rpz[0] == 0)
		*cmd = (*cmd)->next;
	if ((*fz)->nb[0] % g_nb->tb[0] != 1)
		ft_putchar('\n');
	if ((*fz)->mode[3] != 6 && ((*cmd)->c[0] == '\0' || (if_only_i(ed_str(*cmd,
		NULL, (*fz)->nb[0] - giv_last(*fz)), ' '))) && (*fz)->cmd == NULL)
		return (env);
	else if (parsing(*cmd, *fz, &ex, env) == 1)
	{
		add_his(hs, NULL, *fz);
		env = launchcmd(ex, env);
		free_all_ex(&ex);
		free((*fz)->cmd);
		(*fz)->cmd = NULL;
	}
	else if ((*fz)->mode[3] == 0)
	{
		add_his(hs, NULL, *fz);
		free((*fz)->cmd);
		(*fz)->cmd = NULL;
	}
	return (env);
}

void	add_his(t_his **hs, t_his *nw, t_froz *fz)
{
	if (!(fz->cmd && (nw = (t_his*)malloc(sizeof(t_his)))))
		return ;
	nw->cmd = ft_strdup(fz->cmd);
	while ((*hs)->prev != NULL)
		*hs = (*hs)->prev;
	if (if_only(nw->cmd, ' ') || ((*hs)->next->cmd && ft_strcmp(nw->cmd,
		(*hs)->next->cmd) == 0))
	{
		free(nw->cmd);
		free(nw);
		return ;
	}
	(*hs)->next->prev = nw;
	nw->next = (*hs)->next;
	nw->prev = *hs;
	(*hs)->next = nw;
	*hs = (*hs)->next;
}

void	redirection_no_cmd(t_cmd **ex, t_env **env, t_exec *s)
{
	s->in = dup(0);
	s->out = dup(1);
	if (redirection_check_create(*ex))
		redirecting_exec(ex, env, NULL, s);
	dup2(s->out, 1);
	dup2(s->in, 0);
	while ((*ex)->type >= 6 && (*ex)->type <= 11)
		*ex = (*ex)->next;
}

void	move_on(t_cmd **ex, int i)
{
	*ex = (*ex)->next;
	if (i == 4)
		while ((*ex)->type != 5 && (*ex)->type != 13 && (*ex)->type != 42)
			*ex = (*ex)->next;
	else if (i == 5)
		while ((*ex)->type != 4 && (*ex)->type != 13 && (*ex)->type != 42)
			*ex = (*ex)->next;
}

t_env	*exec_fct_re(t_cmd **ex, t_env *env, t_exec *s)
{
	char	**arr;

	arr = ft_strsplit((*ex)->cmd, ' ');
	env = exec_fct(arr, env, s);
	free_tab(arr);
	*ex = (*ex)->next;
	return (env);
}

t_env	*launchcmd(t_cmd *ex, t_env *env)
{
	t_exec	s;

	init_launch(&s, &ex);
	while (ex->next != NULL)
	{
		if (pipe_on(ex))
			env = pipe_fct(&s, &ex, env);
		else if (ex->type == 4 && s.ok == 0)
			move_on(&ex, 4);
		else if (ex->type == 5 && s.ok == 1)
			move_on(&ex, 5);
		else if (ex->type == 0 && !(ex->next->type >= 6 &&
			ex->next->type <= 11))
			env = exec_fct_re(&ex, env, &s);
		else if (ex->type == 0 && ex->next->type >= 6 && ex->next->type <= 11)
			redirection_fork(&ex, &env, &s);
		else if (ex->type >= 6 && ex->type <= 11)
			redirection_no_cmd(&ex, &env, &s);
		else
			ex = ex->next;
	}
	return (env);
}
