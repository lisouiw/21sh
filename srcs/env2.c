/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:54:54 by ltran             #+#    #+#             */
/*   Updated: 2018/04/03 11:58:03 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	lst_add_tenv(t_env **alst, t_env *new)
{
	t_env	*lst;

	lst = *alst;
	if (lst == NULL)
	{
		*alst = new;
	}
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
}

t_env	*t_env_tmp(t_env *env)
{
	t_env *tmp;
	t_env *cpy_head;
	t_env *cpy_tmp;

	cpy_head = NULL;
	if (env == NULL)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		cpy_tmp = ft_memalloc(sizeof(t_env));
		cpy_tmp->name = ft_strdup(tmp->name);
		cpy_tmp->ctn = ft_strdup(tmp->ctn);
		lst_add_tenv(&cpy_head, cpy_tmp);
		tmp = tmp->next;
	}
	return (cpy_head);
}

int		env_flags_check(char **cut)
{
	if (!cut[1])
		return (0);
	if (ft_strequ(cut[1], "-i"))
	{
		if (!cut[2])
			return (1);
		return (2);
	}
	if (ft_strchr(cut[1], '='))
	{
		if (!cut[2])
			return (3);
		return (4);
	}
	else
		return (5);
}

void	set_new_env(char **cut, t_env *env, t_exec *s)
{
	int i;

	i = -1;
	while (cut[++i] && ft_strchr(cut[i], '='))
		b_export(cut[i], &env);
	if (cut[i])
		env = exec_fct(&cut[i], env, s);
	else
		ecriture_info(env);
}

void	builtin_env(char **cut, t_env *env, t_exec *s)
{
	int		flags;
	t_env	*env_cpy;
	t_env	*env_empty;

	env_cpy = NULL;
	env_empty = NULL;
	flags = env_flags_check(cut);
	if (!flags)
		ecriture_info(env);
	if (flags == 2)
	{
		set_new_env(cut + 2, env_empty, s);
		free_list(&env_empty);
	}
	if (flags == 3 || flags == 4)
	{
		env_cpy = t_env_tmp(env);
		set_new_env(cut + 1, env_cpy, s);
		free_list(&env_cpy);
	}
	if (flags == 5)
		ft_putendl("usage: env [-i] [NAME=value ...] [utility [argument ...]]");
}
