/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:59:24 by ltran             #+#    #+#             */
/*   Updated: 2018/04/04 10:27:25 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		give_path(t_env *env, char **cut, int i, char **tab_env)
{
	char	**path;
	char	*cmd;
	pid_t	father;
	int		a;

	a = -1;
	while (env && env->next != NULL && ft_strcmp("PATH=", env->name) != 0)
		env = env->next;
	if (env && ft_strcmp("PATH=", env->name) == 0 &&
			(path = ft_strsplit(env->ctn, ':')))
	{
		while (path[++i] && a == -1 && (cmd = t_strjoin(path[i], "/", cut[0])))
		{
			if ((a = access(cmd, F_OK)) == 0)
			{
				if ((father = fork()) < 0)
					exit(1);
				if (wait(NULL) && father == 0)
					execve(cmd, cut, tab_env);
			}
			free(cmd);
		}
		free_tab(path);
	}
	return (a);
}

char	**list_to_tab(t_env *env, char **tab_env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		++i;
	}
	if (!(tab_env = (char**)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		tab_env[i++] = ft_strjoin(env->name, env->ctn);
		env = env->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

void	print_tab(char **ta, int i)
{
	while (ta[++i])
	{
		ft_putstr_fd(ta[i], 1);
		if (ta[i + 1])
			write(1, " ", 1);
	}
	ft_putchar_fd('\n', 1);
}
