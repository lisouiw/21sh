/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_doc_delim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:15:51 by ltran             #+#    #+#             */
/*   Updated: 2018/04/10 10:57:56 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		add_delim(t_froz *fz, t_cmd *ex)
{
	fz->mode[3] = 6;
	while (ex->prev->prev != NULL)
		ex = ex->prev;
	while (ex->cmd != NULL)
	{
		if (ex->type == 6)
			add_here_struct(fz, ex->cmd);
		ex = ex->next;
	}
	return (check_struct(fz));
}

void	add_doc_s(t_froz *fz, char *s)
{
	int fd;

	fd = 0;
	if (ft_strcmp(s, fz->here->delim) == 0)
	{
		fz->here->ok[0] = 1;
		fd = open("/tmp/fd_for_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fz->here->doc && fz->here->doc != NULL)
			ft_putendl_fd(fz->here->doc, fd);
		close(fd);
		free(s);
	}
	else if (fz->here->doc == NULL)
		fz->here->doc = s;
	else
		fz->here->doc = strjoin_free(s,
			strjoin_free("\n", fz->here->doc, 2), 3);
}

int		add_doc(t_froz *fz, char *s)
{
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	while (fz->here->ok[0] == 1)
		fz->here = fz->here->next;
	add_doc_s(fz, s);
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	return (0);
}
