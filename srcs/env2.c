#include "../twenty.h"

void		lst_add_tenv(t_env **alst, t_env *new)
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

t_env *t_env_tmp(t_env *env)
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

int env_flags_check(char **cut)
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

void builtin_env(char **cut, t_env *env)
{
	int flags;
	t_env *cpy;

	cpy = NULL;
	flags = env_flags_check(cut);
	if (flags)
		cpy = t_env_tmp(env);
	else
		ecriture_info(env);
	if (flags == 1)
		;
	if (flags == 2)
		env = exec_fct(&cut[2], NULL, NULL);
	if (flags == 3 || flags == 4)
	{
		b_export(cut[1], &cpy);
		if (flags == 3)
			ecriture_info(cpy);
		else if (flags == 4)
			exec_fct(cut + 2, cpy, NULL);
	}
}