/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 12:18:12 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:36:07 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t n)
{
	unsigned int	p;
	unsigned int	g;
	unsigned int	i;
	unsigned int	d;

	p = ft_strlen(dst) + ft_strlen(src);
	g = n + ft_strlen(src);
	i = ft_strlen(dst);
	d = 0;
	if (i < n)
	{
		while (src[d] != '\0' && i < (n - 1))
		{
			dst[i] = src[d];
			d++;
			i++;
		}
		dst[i] = '\0';
		return (p);
	}
	return (g);
}
