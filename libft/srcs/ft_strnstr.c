/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 10:50:27 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:37:13 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] != '\0' && len >= (size_t)ft_strlen((char *)little) && len--)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	if (little[0] == '\0')
		return ((char *)big + i);
	return (NULL);
}
