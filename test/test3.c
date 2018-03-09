#include "../twenty.h"

void	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
			close(oldfd);
	}
}

void	exec_pipeline(char ***cmds, char **env, int pos, int in_fd)
{
	pid_t	process;
	int		fd[2];
	int		status;

	if (cmds[pos + 1] == NULL)
	{
		redirect(in_fd, STDIN_FILENO);
		ft_putstr("\nRedirecting fd ");ft_putnbr(in_fd);ft_putstr(" into fd ");ft_putnbr(STDIN_FILENO);ft_putchar('\n');
		ft_putstr("Executing command ");ft_putendl(cmds[pos][0]);
		ft_putchar('\n');
		execve(cmds[pos][0], cmds[pos], env);
	}
	else
	{
		pipe(fd);
		process = fork();
		if (process == 0)
		{
			ft_putendl("Entering Child Process");
			close(fd[0]);
			ft_putendl(" Closing read pipe");
			ft_putstr("  Redirecting fd ");ft_putnbr(in_fd);ft_putstr(" into fd ");ft_putnbr(STDIN_FILENO);ft_putchar('\n');
			redirect(in_fd, STDIN_FILENO);
			ft_putstr("   Redirecting fd ");ft_putnbr(fd[1]);ft_putstr(" into fd ");ft_putnbr(STDOUT_FILENO);ft_putchar('\n');
			ft_putstr("    Executing command ");ft_putendl(cmds[pos][0]);
			redirect(fd[1], STDOUT_FILENO);
			execve(cmds[pos][0], cmds[pos], env);
		}
		else
		{
			waitpid(process, &status, 0);
			ft_putendl("   Closing writting pipe");
			ft_putstr("  Closing pipe ");ft_putnbr(in_fd);ft_putchar('\n');
			close(fd[1]);
			close(in_fd);
			exec_pipeline(cmds, env, pos + 1, fd[0]);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	char	***commands;
	int		i;
	int		j;

	i = -1;
	if (!(commands = (char***)malloc(sizeof(char**) * ac)))
		return (0);
	commands[ac - 1] = NULL;
	while (++i < ac - 1)
		commands[i] = ft_strsplit(av[i + 1], ' ');
	exec_pipeline(commands, env, 0, STDIN_FILENO);
	return (0);
}