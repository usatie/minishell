/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:26:01 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 13:08:41 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#include "libft.h"
#include "minishell.h"

static void	forkexec(t_pipeline *command);
static char	*find_path(char *cmd);

static void	exec_pipelines(t_pipeline *pipelines)
{
	t_pipeline	*cur;

	cur = pipelines;
	while (cur)
	{
		forkexec(cur);
		cur = cur->next;
	}
}

static int	wait_pipelines(t_pipeline *pipelines, int *stat_loc)
{
	bool		interrupted;
	t_pipeline	*cur;

	interrupted = false;
	cur = pipelines;
	// TODO: SIGINT, SARESTART, etc...
	while (cur)
	{
		errno = 0;
		if (waitpid(cur->pid, stat_loc, 0) < 0)
		{
			if (errno == EINTR)
				interrupted = true;
			else if (errno == ECHILD)
				*stat_loc = 0; // ?
			else
				fatal_exit("waitpid()");
		}
		cur = cur->next;
	}
	if (interrupted)
		return (-1);
	return (0);
}

int	forkexec_pipeline(t_pipeline *pipelines)
{
	int			status;

	status = 0;
	exec_pipelines(pipelines);
	if (wait_pipelines(pipelines, &status) < 0)
		return (128 + SIGINT);
	return (WEXITSTATUS(status));
}

//               pipe_from_terminal_stdin
// par __ child1
//     |    ||   pipe1
//     |_ child2
//     |    ||   pipe2
//     |_ child3
//               pipe_to_terminal_stdout
static void	close_dup_pipes(t_pipeline *pipeline)
{
	ft_close(pipeline->inpipe[1]); // write end is not necessary
	ft_close(pipeline->outpipe[0]); // read end is not necessary
	ft_dup2(pipeline->inpipe[0], STDIN_FILENO);
	ft_dup2(pipeline->outpipe[1], STDOUT_FILENO);
}

static void	exec_pipeline(t_pipeline *pipeline)
{
	char	*name;
	char	*path;

	name = pipeline->argv[0];
	// Empty command
	if (name == NULL)
		exit(0);
	// Builtin
	if (isbuiltin(name))
	{
		exec_builtin(pipeline);
		exit(0);
	}
	path = find_path(name);
	// No such file
	if (path == NULL)
		err_exit(name);
	// Execute
	execve(path, pipeline->argv, environ);
	fatal_exit("execve");
}

static void	forkexec(t_pipeline *pipeline)
{
	pipeline->pid = ft_fork();
	if (pipeline->pid == 0)
	{
		// child
		close_dup_pipes(pipeline);
		// redirect
		redirect(pipeline->redirects);
		// execute
		exec_pipeline(pipeline);
	}
	// parent
	if (pipeline->inpipe[0] != STDIN_FILENO)
		ft_close(pipeline->inpipe[0]); // inpipe is not necessary anymore
	ft_close(pipeline->inpipe[1]); // inpipe is not necessary anymore
}

// find_path("cat") -> "/bin/cat"
static char	*find_path(char *cmd)
{
	char	*path;
	char	*envpath;
	char	**paths;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = calloc(sizeof(char), PATH_MAX);
	envpath = getenv("PATH");
	paths = ft_split(envpath, ':');
	i = 0;
	while (paths[i])
	{
		strcpy(path, paths[i]);
		strcat(path, "/");
		strcat(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	free(path);
	return (NULL);
}
