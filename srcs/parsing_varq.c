/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_varq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:08:03 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 22:11:57 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_varq	*add_struct_varq(char *s, t_varq *v)
{
	t_varq	*tmp;
	t_varq	*tmp2;

	if (v == NULL)
	{
		v = (t_varq*)malloc(sizeof(t_varq));
		v->cmd = s;
		v->next = NULL;
	}
	else
	{
		tmp = v;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp2 = (t_varq*)malloc(sizeof(t_varq));
		tmp2->cmd = s;
		tmp2->next = NULL;
		tmp->next = tmp2;
	}
	return (v);
}

t_varq	*add_varq(char *s, int *i, t_varq *v, t_env *env)
{
	if (s[*i] == 39)
		v = varq_simple_quote(s, &(*i), v);
	else if (s[*i] == 34)
		v = varq_double_quote(s, &(*i), v, env);
	else
		v = varq_env(s, &(*i), v, env);
	return (v);
}

t_varq	*add_varq_loop(char *s, t_varq *v, t_env *env)
{
	int		i;

	if (env)
		;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] != 34 && s[i] != 39 && s[i] != '$')
			++i;
		if (s[i])
			v = add_varq(s, &i, v, env);
	}
	return (v);
}

char	*replace_nwl_spc(char *s)
{
	int		i;
	int		q;

	q = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 39 && q != 2)
			q = (q == 1) ? 0 : 1;
		else if (s[i] == 34 && q != 1)
			q = (q == 2) ? 0 : 2;
		else if (s[i] == '\n' && q == 0)
			s[i] = ' ';
	}
	return (s);
}

char	*quote_variable(char *s, t_varq *v, t_env *env)
{
	char	*nw;

	nw = NULL;
	s = replace_nwl_spc(s);
	v = add_varq_loop(s, NULL, env);
	if (v != NULL)
		nw = change_w_varq(s, v);
	else
		return (s);
	free(s);
	free_varq(v);
	return (nw);
}
