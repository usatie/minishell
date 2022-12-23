/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:26:01 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 18:14:19 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"

static void	forkexec(t_pipeline *pipeline);
static void	wait_pipelines(t_pipeline *pipelines, int *stat_loc);

int	exec_pipelines(t_pipeline *pipelines)
{
	int			status;

	status = 0;
	forkexec(pipelines);
	wait_pipelines(pipelines, &status);
	if (WIFSIGNALED(status))
	{
		write(STDERR_FILENO, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

static void	forkexec(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	prepare_pipes_before_fork(pipeline);
	pipeline->pid = ft_fork();
	if (pipeline->pid == 0)
	{
		default_signal(SIGQUIT);
		prepare_pipes_child(pipeline);
		redirect(pipeline->redirects);
		ft_execvp(pipeline->argv[0], pipeline->argv);
	}
	prepare_pipes_parent(pipeline);
	forkexec(pipeline->next);
}

static void	wait_pipelines(t_pipeline *pipelines, int *stat_loc)
{
	int			status;
	int			num_pipelines;
	pid_t		last_pid;
	pid_t		wait_result;

	num_pipelines = pipeline_len(pipelines);
	last_pid = pipeline_last_pid(pipelines);
	while (num_pipelines > 0)
	{
		wait_result = wait(&status);
		if (wait_result < 0)
		{
			if (errno == EINTR)
				continue ;
			fatal_exit("waitpid");
		}
		else if (wait_result == last_pid)
			*stat_loc = status;
		num_pipelines--;
	}
}
