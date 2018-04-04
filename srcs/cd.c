/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:16:28 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 15:11:22 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	cd_prev(t_env **env, char *buf)
{
	t_env	*tmp;
	char	*b;

	tmp = *env;
	while (tmp && tmp->next != NULL && ft_strcmp(tmp->name, "OLDPWD=") != 0)
		tmp = tmp->next;
	if (tmp && ft_strcmp(tmp->name, "OLDPWD=") == 0)
	{
		if (chdir(tmp->ctn) == 0)
		{
			b_export((b = ft_strjoin("OLDPWD=", buf)), &(*env));
			free(b);
			getcwd(buf, PATH_MAX);
			b_export((b = ft_strjoin("PWD=", buf)), &(*env));
			free(b);
			ft_putendl(buf);
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(tmp->ctn);
		}
	}
	else
		ft_putendl("sh: cd: OLDPWD not set");
}

void	cd_home(t_env **env, char *buf)
{
	char	*b;
	t_env	*tmp;

	tmp = *env;
	while (tmp && tmp->next != NULL && ft_strcmp(tmp->name, "HOME=") != 0)
		tmp = tmp->next;
	if (tmp && ft_strcmp(tmp->name, "HOME=") == 0)
	{
		if (chdir(tmp->ctn) == 0)
		{
			b_export((b = ft_strjoin("OLDPWD=", buf)), &(*env));
			free(b);
			getcwd(buf, PATH_MAX);
			b_export((b = ft_strjoin("PWD=", buf)), &(*env));
			free(b);
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(tmp->ctn);
		}
	}
	else
		ft_putendl("sh: cd: HOME not set");
}

void	cd_name(t_env **env, char *cd, char *user, char *buf)
{
	char	*b;

	user = ft_strjoin("/Users/", &cd[1]);
	if (chdir(user) == 0)
	{
		b_export((b = ft_strjoin("OLDPWD=", buf)), &(*env));
		free(b);
		getcwd(buf, PATH_MAX);
		b_export((b = ft_strjoin("PWD=", buf)), &(*env));
		free(b);
	}
	else
	{
		ft_putstr_fd("cd: no such user or named directory: ", 2);
		ft_putendl_fd(cd, 2);
	}
	free(user);
}

void	cd_simple(t_env **env, char *cd, char *buf, char *real)
{
	char		*b;

	if (chdir(cd) == 0)
	{
		b_export((b = ft_strjoin("OLDPWD=", buf)), &(*env));
		free(b);
		getcwd(buf, 127);
		b_export((b = ft_strjoin("PWD=", buf)), &(*env));
		free(b);
	}
	else
	{
		if (access(cd, F_OK) == 0)
			ft_putstr_fd("cd: permission denied: ", 2);
		else
			ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(real, 2);
	}
}

void	b_cd(char *cd, t_env **env)
{
	char	buf[PATH_MAX - 1];
	char	*way;

	getcwd(buf, PATH_MAX);
	way = t_strjoin(buf, "/", cd);
	if (cd && ft_strcmp(cd, "-") == 0)
		cd_prev(env, buf);
	else if ((!(cd) || ft_strcmp(cd, "~") == 0))
		cd_home(env, buf);
	else if (cd[0] == '~')
		cd_name(env, cd, NULL, buf);
	else
		cd_simple(env, cd[0] == '/' ? cd : way, buf, cd);
	free(way);
}
