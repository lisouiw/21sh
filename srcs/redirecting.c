/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:25:25 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 14:03:19 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	redirection(t_cmd **ex, t_env **env, t_exec *s)
{
	char	**arr;

	arr = ft_strsplit((*ex)->cmd, ' ');
	*ex = (*ex)->next;
	if (redirection_check_create(*ex))
		redirecting_exec(ex, env, arr, s);
	else
		exit(-1);
	free_tab(arr);
	while ((*ex)->type >= 6 && (*ex)->type <= 11)
		*ex = (*ex)->next;
}

void	redirection_fork(t_cmd **ex, t_env **env, t_exec *s)
{
	char	**arr;
	int		status;
	pid_t	pid;

	s->in = dup(0);
	s->out = dup(1);
	arr = ft_strsplit((*ex)->cmd, ' ');
	*ex = (*ex)->next;
	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (redirection_check_create(*ex))
			redirecting_exec(ex, env, arr, s);
		else
			exit(-1);
	}
	else
	{
		waitpid(-1, &status, 0);
		s->ok = WEXITSTATUS(status) == 0 ? 1 : 0;
	}
	dup2(1, s->out);
	dup2(0, s->in);
	free_tab(arr);
	while ((*ex)->type >= 6 && (*ex)->type <= 11)
		*ex = (*ex)->next;
}

char	**give_seven(t_cmd *ex)
{
	while (ex->next->type >= 6 && ex->next->type <= 11)
		ex = ex->next;
	while (ex->type >= 8 && ex->type <= 11)
		ex = ex->prev;
	if (ex->type == 6)
	{
		dup2(open("/tmp/in", O_RDONLY), 0);
		while ((ex->type >= 6 && ex->type <= 11) || ex->type == 0)
			ex = ex->next;
		return (NULL);
	}
	else if (ex->type != 7)
		return (NULL);
	return (ft_strsplit(ex->cmd, ' '));
}

void	redirecting_exec(t_cmd **ex, t_env **env, char **arr, t_exec *s)
{
	int		nw;
	char	**tmp;

	if ((tmp = give_seven(*ex)) != NULL)
	{
		nw = (tmp[2] == NULL) ? open(tmp[1], O_RDWR) : open(tmp[2], O_RDONLY);
		dup2(nw, (tmp[2] == NULL ? 0 : ft_atoi(tmp[0])));
		free_tab(tmp);
	}
	if (arr != NULL)
	{
		wait(0);
		*env = exec_fct_nf(arr, *env, ex, s);
	}
}
