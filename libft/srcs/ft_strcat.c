/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:31:18 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:35:01 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcat(char *restrict dst, const char *restrict src)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (dst[i] != '\0')
		i++;
	while (src[c] != '\0')
	{
		dst[i] = src[c];
		i++;
		c++;
	}
	dst[i] = '\0';
	return (dst);
}
