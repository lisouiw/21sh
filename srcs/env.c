/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:53:54 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:17:43 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	b_setenv(char **cut, t_env *env)
{
	int		i;

	i = 0;
	if (!cut[1])
		ecriture_info(env);
	else
		while (cut[++i])
			b_export(cut[i], &env);
}

void	b_export(char *cut, t_env **env)
{
	t_env	*tmp;
	t_env	*kp;

	tmp = NULL;
	kp = *env;
	if (if_chr_ex(cut, '='))
	{
		tmp = add_env(cut, NULL, ft_strlen(ft_strchr(cut, '=')),
				ft_strlen(cut));
		while (kp && kp->next != NULL && ft_strcmp(kp->name, tmp->name) != 0)
			kp = kp->next;
		if (kp && ft_strcmp(kp->name, tmp->name) == 0)
		{
			free(kp->name);
			kp->name = ft_strdup(tmp->name);
			free(kp->ctn);
			kp->ctn = ft_strdup(tmp->ctn);
		}
		else
		{
			*env = add_env(cut, *env, ft_strlen(ft_strchr(cut, '=')),
					ft_strlen(cut));
		}
		free_elem(tmp);
	}
}

void	b_unset(char **cut, t_env **env, int i)
{
	t_env	*kp;
	t_env	*sup;

	while (cut[++i] && (kp = *env))
	{
		if (ft_strcmp(kp->name, cut[i]) == 61)
		{
			(*env) = (*env)->next;
			free_elem(kp);
		}
		else
		{
			while (kp && kp->next != NULL)
			{
				if (ft_strcmp(kp->next->name, cut[i]) == 61)
				{
					sup = kp->next;
					kp->next = kp->next->next;
					free_elem(sup);
					break ;
				}
				kp = kp->next;
			}
		}
	}
}

t_env	*add_env(char *environ, t_env *env, size_t one, size_t all)
{
	t_env	*new;
	t_env	*tmp;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	new->name = ft_strsub(environ, 0, all - one + 1);
	new->ctn = ft_strsub(environ, all - one + 1, one - 1);
	new->next = NULL;
	if (!(env))
		return (new);
	tmp = env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (env);
}

t_env	*give_env(t_env *env)
{
	int				i;
	extern char		**environ;

	i = -1;
	while (environ[++i])
	{
		env = add_env(environ[i], env, ft_strlen(ft_strchr(environ[i], '=')),
				ft_strlen(environ[i]));
	}
	return (env);
}
