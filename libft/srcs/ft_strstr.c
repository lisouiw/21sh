/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 10:17:16 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:37:42 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char *a;
	char *b;

	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		a = (char *)big;
		b = (char *)little;
		while (*b && *a == *b)
		{
			a++;
			b++;
		}
		if (*b == '\0')
			return ((char *)big);
		big++;
	}
	return (NULL);
}
