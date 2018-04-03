/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:17:26 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 23:25:23 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	end_pipe(t_cmd **ex, t_exec **s, int pp)
{
	int		status;

	signal(SIGCHLD, SIG_DFL);
	if (pp == 0)
	{
		waitpid(-1, &status, 0);
		(*s)->ok = WEXITSTATUS(status) == 0 ? 1 : 0;
		wait(NULL);
	}
	close((*s)->p[1]);
	dup2(1, (*s)->out);
	dup2(0, (*s)->in);
	while ((*ex)->type != 3 && (*ex)->type != 4 && (*ex)->type != 5
		&& (*ex)->type != 13 && (*ex)->type != 42)
		*ex = (*ex)->next;
	(*s)->in = (*s)->p[0];
}

int		pipe_on(t_cmd *ex)
{
	while (ex->type != 3 && ex->type != 4 && ex->type != 5 && ex->type != 13
		&& ex->type != 42)
		ex = ex->next;
	if (ex->type == 3 && ex->next->type == 0)
	{
		ex = ex->next;
		return (1);
	}
	else if (ex->type == 3)
		return (1);
	return (0);
}

void	pipe_exec(t_exec *s, t_cmd **ex, t_env *env, int pp)
{
	dup2(s->in, 0);
	if (pp)
		dup2(s->p[1], 1);
	close(s->p[0]);
	if ((*ex)->type >= 6 && (*ex)->type <= 11)
	{
		redirection_no_cmd(ex, &env, &(*s));
		exit(0);
	}
	else if ((*ex)->next->type >= 6 && (*ex)->next->type <= 11)
		redirection(ex, &env, &(*s));
	else if ((*ex)->type == 0)
		env = exec_fct_nf(ft_strsplit((*ex)->cmd, ' '), env, ex, s);
}

t_env	*pipe_fct(t_exec *s, t_cmd **ex, t_env *env)
{
	int		i;
	int		pp;
	pid_t	pid;

	i = 0;
	pp = 1;
	s->in = 0;
	while (pp == 1)
	{
		s->out = dup(1);
		pp = pipe_on(*ex);
		if ((*ex)->cmd == NULL)
			return (env);
		pipe(s->p);
		if (!((*ex)->type == 0 || ((*ex)->type >= 6 && (*ex)->type <= 11)))
			*ex = (*ex)->next;
		else if ((pid = fork()) == -1)
			exit(-1);
		else if (pid == 0)
			pipe_exec(s, ex, env, pp);
		else
			end_pipe(&(*ex), &s, pp);
	}
	return (env);
}
