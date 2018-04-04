/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:20:12 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:33:14 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	free_ed(t_edit **ed, t_froz *fz)
{
	if ((*ed)->rpz[0] == 1 && (*ed)->rpz[1] == 1)
		return ;
	while ((*ed)->rpz[0] == 0)
		*ed = (*ed)->next;
	while ((*ed)->rpz[1] == 0)
	{
		*ed = (*ed)->next;
		free((*ed)->prev);
	}
	(*ed)->rpz[0] = 1;
	(*ed)->rpz[2] = giv_last(fz);
	(*ed)->rpz[3] = giv_last(fz);
	(*ed)->rpz[4] = 0;
	(*ed)->prev = *ed;
	(*ed)->next = *ed;
}

void	free_list(t_env **env)
{
	t_env	*tmp;

	while (*env != NULL)
	{
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->ctn);
		free(*env);
		*env = tmp;
	}
}

char	*t_strjoin(char *f, char *s, char *t)
{
	char	*way;
	char	*tmp;

	tmp = ft_strjoin(f, s);
	way = ft_strjoin(tmp, t);
	free(tmp);
	return (way);
}

void	free_tab(char **array)
{
	int		i;

	if (array)
	{
		i = -1;
		while (array[++i] != NULL)
		{
			ft_strdel(&array[i]);
			free(array[i]);
		}
	}
	free(array);
	array = NULL;
}
