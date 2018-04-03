/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_varq_fct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:02:57 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 13:03:44 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_varq	*varq_simple_quote(char *s, int *i, t_varq *v)
{
	int		y;
	char	*tmp;

	y = *i + 1;
	while (s[++(*i)] != 39 && s[*i])
		;
	tmp = ft_strsub(s, y, *i - y);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
	}
	v = add_struct_varq(tmp, v);
	(*i)++;
	return (v);
}

t_varq	*varq_double_quote(char *s, int *i, t_varq *v, t_env *env)
{
	int		y;

	y = *i + 1;
	while (s[++(*i)] != 34 && s[*i])
		;
	v = add_struct_varq(translate_dquote(ft_strsub(s, y, *i - y), env), v);
	(*i)++;
	return (v);
}

t_varq	*varq_env(char *s, int *i, t_varq *v, t_env *env)
{
	int		y;

	if (s[*i] == '$' && s[(*i + 1)] == '$')
	{
		y = *i;
		while (s[++(*i)] && s[(*i + 1)] == '$')
			;
		v = add_struct_varq(ft_strsub(s, y, *i - y), v);
	}
	else
	{
		y = *i + 1;
		while (s[++(*i)] && s[*i] != ' ' && s[*i] != '$' && s[*i] != 34 && s[*i] != 39)
			;
		if (y - *i == 0)
			v = add_struct_varq(ft_strsub(s, y - 1, 1), v);
		else
			v = add_struct_varq(search_var_env(ft_strsub(s, y, *i - y), env), v);
	}
	return (v);
}
