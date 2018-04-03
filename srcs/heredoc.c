/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:46:25 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 15:33:47 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	add_here_struct(t_froz *fz, char *s)
{
	char	**t;

	t = ft_strsplit(s, ' ');
	if ((!fz->here->delim) && fz->here->prev == NULL && fz->here->next == NULL)
	{
		fz->here->delim = ft_strdup(t[1]);
		fz->here->doc = NULL;
		fz->here->ok[0] = 0;
		fz->here->prev = NULL;
		fz->here->next = (t_here*)malloc(sizeof(t_here));
		fz->here->next->prev = fz->here;
		fz->here = fz->here->next;
		fz->here->delim = NULL;
		fz->here->next = NULL;
	}
	else if (fz->here->delim == NULL)
	{
		fz->here->delim = ft_strdup(t[1]);
		fz->here->doc = NULL;
		fz->here->ok[0] = 0;
		fz->here->next = (t_here*)malloc(sizeof(t_here));
		fz->here->next->prev = fz->here;
		fz->here = fz->here->next;
		fz->here->delim = NULL;
		fz->here->next = NULL;
	}
	else
		fz->here = fz->here->next;
	free_tab(t);
}

int		check_struct(t_froz *fz)
{
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	while (fz->here->delim != NULL && fz->here->ok[0] == 1)
		fz->here = fz->here->next;
	if (fz->here->delim == NULL && fz->here->next == NULL)
		fz->mode[3] = 0;
	else
		fz->mode[3] = 6;
	while (fz->here->prev != NULL)
		fz->here = fz->here->prev;
	return (fz->mode[3]);
}

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
		fd = open("/tmp/in", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fz->here->doc && fz->here->doc != NULL)
			ft_putendl_fd(fz->here->doc, fd);
		close(fd);
		free(s);
	}
	else if (fz->here->doc == NULL)
		fz->here->doc = s;
	else
		fz->here->doc = strjoin_free(s, strjoin_free("\n", fz->here->doc, 2), 3);
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
