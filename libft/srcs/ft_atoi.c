/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:34:43 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:30:44 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		ft_vide(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == '\f' || str[i] == '\v' || str[i] == '\r' ||
	str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int				ft_atoi(const char *str)
{
	int					i;
	unsigned int		nb;
	int					ent;
	int					sgn;

	i = ft_vide(str);
	nb = 0;
	ent = 0;
	sgn = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgn = 1;
		i++;
	}
	else if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		ent = str[i] - 48;
		nb = nb * 10 + ent;
		i++;
	}
	sgn == 1 ? nb = -(nb) : nb;
	return (nb);
}
