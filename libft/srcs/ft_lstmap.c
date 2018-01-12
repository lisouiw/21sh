/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 23:39:32 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:32:15 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;

	res = f(lst);
	tmp = res;
	while (lst->next)
	{
		lst = lst->next;
		res->next = f(lst);
		res = res->next;
	}
	return (tmp);
}
