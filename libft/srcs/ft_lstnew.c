/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 18:33:17 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:32:20 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*w;

	if (!(w = (t_list*)malloc(sizeof(t_list) * (content_size))))
		return (NULL);
	if (content == NULL)
	{
		w->content = NULL;
		w->content_size = 0;
		w->next = NULL;
	}
	else
	{
		w->content = malloc(content_size);
		w->content_size = content_size;
		ft_memcpy(w->content, content, content_size);
		w->next = NULL;
	}
	return (w);
}
