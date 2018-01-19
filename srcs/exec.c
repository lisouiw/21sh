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

	if (((tab_env = list_to_tab(env, NULL)) && access(cut[0], F_OK) == 0))
	{
		if ((fils = fork()) == -1)
			exit(1);
		if (fils == 0)
			if (execve(cut[0], cut, tab_env) == -1)
			{
				ft_putstr("sh: command not found: ");
				ft_putendl(cut[0]);
				free_tab(tab_env);
				exit(-1);
			}
	}
	else
	{
		if (give_path(env, cut, -1, tab_env) == -1)
		{
			ft_putstr("sh: command not found: ");
			ft_putendl(cut[0]);
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

// t_env	*exec_giv(char *line, t_env *env, char **cut, int *i)
// {
// 	i = 0;
// 	if (!(cut = ft_strsplit(line, ' ')) || !cut[0])
// 		;
// 	// else if (ft_strcmp("echo", cut[0]) == 0)
// 	// 	print_tab(cut, 0);
// 	// else if (ft_strcmp("env", cut[0]) == 0)
// 	// 	ecriture_info(env);
// 	// else if (ft_strcmp("setenv", cut[0]) == 0)
// 	// {
// 	// 	while (cut[1] && cut[++(*i)])
// 	// 		b_export(cut[*i], &env);
// 	// }
// 	// else if (env && ft_strcmp("unsetenv", cut[0]) == 0)
// 	// 	b_unset(cut, &env, 0);
// 	// else if (ft_strcmp("cd", cut[0]) == 0)
// 	// 	b_cd(cut[1], &env);
// 	// else if (ft_strcmp(line, "exit") == 0 && free_for_exit(line, cut, env))
// 	// 	exit(0);
// 	else
// 		b_other(cut, env);
// 	// free_tab(cut);
// 	return (env);
// }