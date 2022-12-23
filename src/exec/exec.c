/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:53:54 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 12:53:54 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"
#include <readline/readline.h>

static int	open_redirect_srcfd(t_pipeline *pipelines);
static void	close_redirect_srcfd(t_pipeline *pipelines);

static int	open_redirect_srcfd(t_pipeline *pipelines)
{
	t_redirect	*rd;

	if (!pipelines)
		return (0);
	rd = pipelines->redirects;
	while (rd)
	{
		if (rd->kind == RD_OUTPUT)
			rd->srcfd = open(rd->path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (rd->kind == RD_INPUT)
			rd->srcfd = open(rd->path, O_RDONLY, 0);
		else if (rd->kind == RD_APPEND)
			rd->srcfd = open(rd->path, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (rd->kind == RD_HEREDOC)
			rd->srcfd = read_heredoc(rd->delimiter, rd->is_delim_quoted);
		else
			err_exit("Unexpected Redirect kind");
		if (rd->srcfd < 0)
		{
			perror(rd->path);
			return (-1);
		}
		rd = rd->next;
	}
	return (open_redirect_srcfd(pipelines->next));
}

static void	close_redirect_srcfd(t_pipeline *pipelines)
{
	t_redirect	*redir;

	if (!pipelines)
		return ;
	redir = pipelines->redirects;
	while (redir)
	{
		close(redir->srcfd);
		redir = redir->next;
	}
	close_redirect_srcfd(pipelines->next);
}

int	exec(t_pipeline *pipelines)
{
	int	status;

	g_env.heredoc_interrupted = 0;
	// Open file descriptors for redirections
	if (open_redirect_srcfd(pipelines) < 0)
		status = 1;
	// Heredoc interrupted
	else if (g_env.heredoc_interrupted)
	{
		close_redirect_srcfd(pipelines);
		status = 1;
	}
	// Redirection only
	else if (pipelines->argv[0] == NULL)
		status = 0;
	// Builtin && single command
	else if (isbuiltin(pipelines->argv[0]) && pipelines->next == NULL)
	{
		redirect(pipelines->redirects);
		status = exec_builtin(pipelines->argv);
		restore_redirect(pipelines->redirects);
	}
	// Non-builtin or multiple command
	else
	{
		status = exec_pipelines(pipelines);
		g_env.sig = 0;
	}
	return (status);
}
