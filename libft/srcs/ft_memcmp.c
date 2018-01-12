/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:50:30 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:32:41 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		i;
	unsigned char		*b1;
	unsigned char		*b2;

	i = 0;
	b1 = (unsigned char*)s1;
	b2 = (unsigned char*)s2;
	while (i < n && b1[i] == b2[i])
		i++;
	if (i == n)
		return (0);
	return (b1[i] - b2[i]);
}
