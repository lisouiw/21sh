/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 17:14:04 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:32:36 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	const char		*s1;
	char			*b;

	s1 = s;
	b = (char *)s1;
	i = 0;
	while (i < n)
	{
		if (b[i] == (char)c)
			return (b + i);
		i++;
	}
	return (NULL);
}
