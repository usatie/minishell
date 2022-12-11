#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	ft_close(int fd)
{
	if (fd < 0)
		return ;
	if (close(fd) < 0)
		err_exit("close()");
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		err_exit("fork()");
	return (pid);
}

void	ft_dup2(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) < 0)
			err_exit("dup2()");
		ft_close(oldfd);
	}
}

//               pipe_from_terminal_stdin
// par __ child1
//     |    ||   pipe1
//     |_ child2
//     |    ||   pipe2
//     |_ child3
//               pipe_to_terminal_stdout
void	forkexec(t_pipeline *command)
{
	command->pid = ft_fork();
	if (command->pid == 0)
	{
		// exec
		ft_close(command->inpipe[1]); // write end is not necessary
		ft_close(command->outpipe[0]); // read end is not necessary
		ft_dup2(command->inpipe[0], STDIN_FILENO);
		ft_dup2(command->outpipe[1], STDOUT_FILENO);
		if (command->argv[0] == NULL)
			exit(0);
		execve(find_path(command->argv[0]), command->argv, NULL);
		err_exit("execve");
	}
	else
	{
		// parent
		ft_close(command->inpipe[0]); // inpipe is not necessary anymore
		ft_close(command->inpipe[1]); // inpipe is not necessary anymore
	}
}

