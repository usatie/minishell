/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:26:01 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 00:17:00 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"

static void	forkexec(t_pipeline *pipeline);
static int	wait_pipelines(t_pipeline *pipelines, int *stat_loc);

int	exec_pipelines(t_pipeline *pipelines)
{
	int			status;

	status = 0;
	forkexec(pipelines);
	if (wait_pipelines(pipelines, &status) < 0)
	{
		write(STDERR_FILENO, "\n", 1);
		return (128 + SIGINT);
	}
	return (WEXITSTATUS(status));
}

static void	forkexec(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	pipeline->pid = ft_fork();
	// child
	if (pipeline->pid == 0)
	{
		prepare_pipes_child(pipeline);
		redirect(pipeline->redirects);
		ft_execvp(pipeline->argv[0], pipeline->argv);
	}
	// parent
	prepare_pipes_parent(pipeline);
	forkexec(pipeline->next);
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
		if (waitpid(cur->pid, stat_loc, 0) < 0)
		{
			if (errno == EINTR)
			{
				interrupted = true;
				continue ;
			}
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
