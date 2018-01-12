/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:25:16 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:37:03 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnew(size_t size)
{
	char				*new;

	new = (char*)malloc(sizeof(char) * (size + 1));
	if (!(new))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
