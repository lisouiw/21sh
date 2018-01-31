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
				if (wait(0) && father == 0)
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

void	b_other(char **cut, t_env *env)
{
	pid_t	fils;
	char	**tab_env;

	if ((tab_env = list_to_tab(env, NULL)))
	{
		if ((fils = fork()) == -1)
			exit(1);
		if (fils == 0)
			if (execve(cut[0], cut, tab_env) == -1)
				if (give_path(env, cut, -1, tab_env) == -1)
				{
					ft_putstr("sh: command not found: ");
					ft_putendl(cut[0]);
					exit(-1);
				}
	}
	free_tab(tab_env);
}

void	print_tab(char **ta, int i)
{
	while (ta[++i])
	{
		ft_putstr(ta[i]);
		if (ta[i + 1])
			write(1, " ", 1);
	}
	putchar('\n');
}
