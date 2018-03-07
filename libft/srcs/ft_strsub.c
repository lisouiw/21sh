/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 17:29:10 by ltran             #+#    #+#             */
/*   Updated: 2018/03/07 16:21:37 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*troncon;

	i = 0;
	troncon = (char *)malloc((sizeof(char) * (len + 1)));
	if (!troncon || !s)
		return (NULL);
	while (i < len)
	{
		troncon[i] = s[start];
		i++;
		start++;
	}
	troncon[len] = '\0';
	return (troncon);
}
