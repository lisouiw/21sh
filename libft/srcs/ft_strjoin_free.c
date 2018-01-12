/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 17:43:13 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:36:02 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int i)
{
	char	*join;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(join))
		return (NULL);
	join = ft_strcpy(join, s1);
	join = ft_strcat(join, s2);
	if (i == 1)
		free(s1);
	if (i == 2)
		free(s2);
	return (join);
}
