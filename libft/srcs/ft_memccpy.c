/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 11:26:08 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:32:32 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
		int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		if (((unsigned char*)src)[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
