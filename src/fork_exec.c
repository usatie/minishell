/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:26:01 by susami            #+#    #+#             */
/*   Updated: 2022/12/15 13:36:18 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#include "libft.h"
#include "minishell.h"

int	ft_open(char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		err_exit("open()");
	return (fd);
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
void	forkexec(t_pipeline *command)
{
	command->pid = ft_fork();
	if (command->pid == 0)
	{
		// child
		// pipe
		ft_close(command->inpipe[1]); // write end is not necessary
		ft_close(command->outpipe[0]); // read end is not necessary
		ft_dup2(command->inpipe[0], STDIN_FILENO);
		ft_dup2(command->outpipe[1], STDOUT_FILENO);
		// redirect
		if (command->out_path)
		{
			int	fd;
			fd = ft_open(command->out_path);
			ft_dup2(fd, command->out_fd);
		}
		// path
		if (command->argv[0] == NULL)
			exit(0);
		// exec
		if (isbuiltin(command->argv[0]))
		{
			exec_builtin(command);
			exit(0);
		}
		else
		{
			char	*path = find_path(command->argv[0]);
			execve(path, command->argv, NULL);
			err_exit("execve");
		}
	}
	else
	{
		// parent
		if (command->inpipe[0] != STDIN_FILENO)
			ft_close(command->inpipe[0]); // inpipe is not necessary anymore
		ft_close(command->inpipe[1]); // inpipe is not necessary anymore
	}
}

// find_path("cat") -> "/bin/cat"
char	*find_path(char *cmd)
{
	char	*path;
	char	*envpath;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = calloc(sizeof(char), PATH_MAX);
	envpath = getenv("PATH");
	paths = ft_split(envpath, ':');
	for (int i = 0; paths[i]; i++)
	{
		strcpy(path, paths[i]);
		strcat(path, "/");
		strcat(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
	}
	free(path);
	return (NULL);
}

int	forkexec_pipeline(t_pipeline *head)
{
	t_pipeline	*pipeline;

	pipeline = head;
	while (pipeline)
	{
		forkexec(pipeline);
		pipeline = pipeline->next;
	}
	// wait all pipeline processes to exit
	pipeline = head;
	while (pipeline)
	{
		if (waitpid(pipeline->pid, &status, 0) < 0 && errno != ECHILD)
			fatal_exit("waitpid()");
		pipeline = pipeline->next;
	}
	return (WEXITSTATUS(status));
}
