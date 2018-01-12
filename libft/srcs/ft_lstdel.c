/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 19:32:08 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:31:54 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*sup;

	sup = *alst;
	if (!alst || !del)
		return ;
	while (sup)
	{
		del(sup->content, sup->content_size);
		free(sup);
		sup = sup->next;
	}
	*alst = NULL;
}
