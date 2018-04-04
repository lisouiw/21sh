/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:27:15 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 16:06:11 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	sig_int(int sig)
{
	int		status;

	status = 0;
	while (ed->rpz[0] == 0)
		ed = ed->next;
	if (ed->rpz[0] == 1 && ed->rpz[1] != 1)
		return ;
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status) && WEXITSTATUS(status) == 0)
		write(1, "\n", 1);
	else
		exit(0);
	sig = 0;
}

void	sig_int3(int sig)
{
	sig = 0;
	while (ed->rpz[0] == 0)
		ed = ed->next;
	if (ed->rpz[0] == 1 && ed->rpz[1] != 1)
		return ;
	fz->mode[3] = 0;
	add_his(&hs, NULL, fz);
	write(1, "\n", 1);
	init_for_new(&hs, &fz, &ed);
}

void	sig_int_here_2(void)
{
	while (ed->rpz[0] == 0)
		ed = ed->next;
	if (ed->rpz[0] == 1 && ed->rpz[1] != 1)
		return ;
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	if (fz->here->next == NULL)
		exit(0);
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	while (fz->here->ok[0] == 1)
		fz->here = fz->here->next;
	fz->here->ok[0] = 1;
}

void	sig_int_here(int sig)
{
	sig_int_here_2();
	sig = open("/tmp/in", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fz->here->doc && fz->here->doc != NULL)
		ft_putendl_fd(fz->here->doc, sig);
	close(sig);
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	if (check_struct(fz) == 0)
	{
		cursor_end(ed);
		env = treat_cmd_here(env, &ed, &hs, &fz);
		fz->mode[3] = check_struct(fz);
		init_for_new(&hs, &fz, &ed);
		init_data(&fz);
	}
}

void	ls_signal(int i)
{
	if (i == 6)
	{
		signal(SIGINT, sig_int_here);
		signal(SIGCHLD, SIG_DFL);
	}
	else if (i != 0)
	{
		signal(SIGINT, sig_int3);
		signal(SIGCHLD, SIG_DFL);
	}
	else
	{
		signal(SIGINT, sig_int);
		signal(SIGCHLD, SIG_DFL);
	}
}
