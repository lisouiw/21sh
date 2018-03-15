#include "../twenty.h"

t_env	*exec_fct_nf(char **cut, t_env *env)
{
	if (ft_strcmp("echo", cut[0]) == 0)
	{

		print_tab(cut, 0);
		exit(0);
	}
	// else if (ft_strcmp("env", cut[0]) == 0)
	// 	ecriture_info(env);
	// else if (ft_strcmp("setenv", cut[0]) == 0)
	// {
	// 	while (cut[1] && cut[++(*i)])
	// 		b_export(cut[*i], &env);
	// }
	// else if (env && ft_strcmp("unsetenv", cut[0]) == 0)
	// 	b_unset(cut, &env, 0);
	// else if (ft_strcmp("cd", cut[0]) == 0)
	// 	b_cd(cut[1], &env);
	else if (ft_strcmp(cut[0], "exit") == 0) // && free_for_exit(line, cut, env))
    {
        printf("exit\n");
        exit(0);
    }
    else
		b_other_nf(cut, env);
		// b_other(ar, env);
    return (env);
}

t_env	*exec_fct(char **cut, t_env *env)
{
	if (ft_strcmp("echo", cut[0]) == 0)
		print_tab(cut, 0);
	// else if (ft_strcmp("env", cut[0]) == 0)
	// 	ecriture_info(env);
	// else if (ft_strcmp("setenv", cut[0]) == 0)
	// {
	// 	while (cut[1] && cut[++(*i)])
	// 		b_export(cut[*i], &env);
	// }
	// else if (env && ft_strcmp("unsetenv", cut[0]) == 0)
	// 	b_unset(cut, &env, 0);
	// else if (ft_strcmp("cd", cut[0]) == 0)
	// 	b_cd(cut[1], &env);
	else if (ft_strcmp(cut[0], "exit") == 0) // && free_for_exit(line, cut, env))
		exit(0);
    else
		b_other(cut, env);
		// b_other(ar, env);

    return (env);
}

void	b_other(char **cut, t_env *env)
{
	char	**tab_env;
    pid_t      pid;
	
	if ((tab_env = list_to_tab(env, NULL)))
	{
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0  && wait(0) && execve(cut[0], cut, tab_env) == -1)
		{
			if (wait(0) && give_path_nf(env, cut, -1, tab_env) == -1)
			{
				ft_putstr("sh: command not found: ");
				ft_putendl(cut[0]);
				exit(-1);
			}
		}
		else 
			wait(0);
	}
	free_tab(tab_env);
}

void	b_other_nf(char **cut, t_env *env)
{
	char	**tab_env;
	
	if ((tab_env = list_to_tab(env, NULL)))
	{
		if (wait(0) && execve(cut[0], cut, tab_env) == -1)
			if (give_path_nf(env, cut, -1, tab_env) == -1)
			{
				exit(0);
				ft_putstr("sh: command not found: ");
				ft_putendl(cut[0]);
				exit(-1);
			}

	}
	
	free_tab(tab_env);
}

int		give_path_nf(t_env *env, char **cut, int i, char **tab_env)
{
	char	**path;
	char	*cmd;
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
				if (wait(0))
					execve(cmd, cut, tab_env);
			}
			free(cmd);
		}
		free_tab(path);
	}
	return (a);
}
