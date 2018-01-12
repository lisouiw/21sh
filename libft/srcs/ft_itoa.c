/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 14:23:59 by ltran             #+#    #+#             */
/*   Updated: 2017/06/23 15:31:39 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		ft_i(int n)
{
	unsigned int	mod;
	unsigned int	i;
	unsigned int	div;

	mod = 0;
	i = 0;
	if (n <= 0)
	{
		i++;
		div = n * -1;
	}
	else
		div = n;
	while (div != 0 || div != mod)
	{
		mod = div % 10;
		div = div / 10;
		i++;
		if (div == 0 && div == mod)
			i--;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	unsigned int	mod;
	unsigned int	div;
	int				i;
	char			*tab;

	i = ft_i(n);
	mod = 0;
	tab = (char*)malloc((sizeof(char)) * (i + 1));
	if (!(tab))
		return (NULL);
	tab[i] = '\0';
	i--;
	div = n;
	if (n < 0)
		div = div * -1;
	while (i >= 0)
	{
		mod = div % 10;
		div = div / 10;
		tab[i] = mod + '0';
		i--;
	}
	if (n < 0)
		tab[0] = '-';
	return (tab);
}
