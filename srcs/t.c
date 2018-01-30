#include "../twenty.h"

void	free_list(t_env **env)
{
	t_env		*tmp;

	while (*env != NULL)
	{
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->ctn);
		free(*env);
		*env = tmp;
	}
}

char	*t_strjoin(char *f, char *s, char *t)
{
	char	*way;
	char	*tmp;

	tmp = ft_strjoin(f, s);
	way = ft_strjoin(tmp, t);
	free(tmp);
	return (way);
}

void	free_tab(char **array)
{
	int		i;

	if (array)
	{
		i = -1;
		while (array[++i])
		{
			ft_strdel(&array[i]);
			free(array[i]);
		}
	}
	free(array);
	array = NULL;
}

int		free_for_exit(char *line, char **cut, t_env *env)
{
	ft_strdel(&line);
	free_tab(cut);
	free_list(&env);
	return (1);
}
