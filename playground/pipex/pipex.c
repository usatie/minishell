#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void	err_exit(char *s) __attribute__((noreturn));
typedef struct s_command	t_command;
struct s_command {
	char		**argv;
	char		*path;
	int			inpipe[2];
	int			outpipe[2];
	t_command	*next;
};

void	err_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
	
void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

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
pid_t	forkexec(t_command *command)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		// exec
		ft_close(command->inpipe[1]); // write end is not necessary
		ft_close(command->outpipe[0]); // read end is not necessary
		ft_dup2(command->inpipe[0], STDIN_FILENO);
		ft_dup2(command->outpipe[1], STDOUT_FILENO);
		execve(command->path, command->argv, NULL);
		err_exit("execve");
	}
	else
	{
		// parent
		ft_close(command->inpipe[0]); // inpipe is not necessary anymore
		ft_close(command->inpipe[1]); // inpipe is not necessary anymore
		return (pid);
	}
}

//t_command	*new_command(char *path, char **argv, int inpipe[2], int outpipe[2])
t_command	*new_command(char *path, char **argv)
{
	t_command	*command;

	command = calloc(1, sizeof(t_command));
	command->path = path;
	command->argv = argv;
	cpy_pipe(command->inpipe, (int []){STDIN_FILENO, -1});
	cpy_pipe(command->outpipe, (int []){-1, STDOUT_FILENO});
	return (command);
}

t_command	*pipe_command(t_command *lhs, t_command *rhs)
{
	lhs->next = rhs;
	if (pipe(lhs->outpipe) < 0)
		err_exit("pipe()");
	cpy_pipe(rhs->inpipe, lhs->outpipe);
	return (rhs);
}

int	main(void)
{
	t_command	*head;
	t_command	*cur;

	// "ls | cat -e | head -1"
	head = cur = new_command("/bin/ls", (char *[]){"ls", NULL});
	cur = pipe_command(cur, new_command("/bin/cat", (char *[]){"cat", "-e", NULL}));
	cur = pipe_command(cur, new_command("/usr/bin/head", (char *[]){"head", "-1", NULL}));

	/*
	// "cat -e pipex.c | grep pipe | sort -r"
	head = cur = new_command("/bin/cat", (char *[]){"cat", "-e", "pipex.c", NULL});
	cur = pipe_command(cur, new_command("/usr/bin/grep", (char *[]){"grep", "pipe", NULL}));
	cur = pipe_command(cur, new_command("/usr/bin/sort", (char *[]){"sort", "-r", NULL}));
	*/

	// forkexec "ls"
	// forkexec "cat -e"
	// forkexec "head -1"
	cur = head;
	while (cur)
	{
		forkexec(cur);
		cur = cur->next;
	}
}
