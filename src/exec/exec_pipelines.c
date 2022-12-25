/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:26:01 by susami            #+#    #+#             */
/*   Updated: 2022/12/26 08:43:59 by susami           ###   ########.fr       */
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

static void	wait_pipelines(t_pipeline *pipelines, int *stat_loc)
{
	t_pipeline	*cur;

	cur = pipelines;
	while (cur)
	{
		if (waitpid(cur->pid, stat_loc, 0) < 0)
		{
			if (errno == EINTR)
				continue ;
			else
				fatal_exit("waitpid()");
		}
		cur = cur->next;
	}
}
