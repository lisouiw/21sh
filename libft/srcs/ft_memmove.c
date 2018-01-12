/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:23:36 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:33:06 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*d;
	const char		*s;

	i = 1;
	d = dst;
	s = src;
	while (i <= n && s < d)
	{
		d[n - i] = s[n - i];
		i++;
	}
	i = 0;
	while (i < n && s >= d)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
