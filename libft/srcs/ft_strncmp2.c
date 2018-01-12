/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:59:44 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:36:46 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*b1;
	unsigned char	*b2;

	i = 0;
	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	if (n == 0 || s1 == NULL || s2 == NULL)
		return (0);
	while (i < n && b1[i] == b2[i] && b1[i] != '\0' && b2[i] != '\0')
		i++;
	return (b1[i] - b2[i]);
}
