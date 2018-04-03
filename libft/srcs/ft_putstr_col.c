/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_col.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:04:12 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 18:52:35 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_col(char *s, char *col)
{
	if (ft_strcmp(col, "red") == 0)
		ft_putstr(ft_strjoin_free("\033[31m",
			ft_strjoin(s, "\033[0m"), 2));
	if (ft_strcmp(col, "green") == 0)
		(ft_putstr(ft_strjoin_free("\033[32m",
		ft_strjoin(s, "\033[0m"), 2)));
	if (ft_strcmp(col, "yellow") == 0)
		(ft_putstr(ft_strjoin_free("\033[33m",
		ft_strjoin(s, "\033[0m"), 2)));
	if (ft_strcmp(col, "blue") == 0)
		ft_putstr(ft_strjoin_free("\033[34m",
		ft_strjoin(s, "\033[0m"), 2));
	if (ft_strcmp(col, "magenta") == 0)
		ft_putstr(ft_strjoin_free("\033[35m",
		ft_strjoin(s, "\033[0m"), 2));
	if (ft_strcmp(col, "cyan") == 0)
		ft_putstr(ft_strjoin_free("\033[36m",
		ft_strjoin(s, "\033[0m"), 2));
	else
		return (ft_putstr(s));
}
