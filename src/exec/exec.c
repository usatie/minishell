/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:53:54 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 15:47:01 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"
#include <readline/readline.h>

static void	open_redirect_srcfd(t_pipeline *pipelines);
static void	close_redirect_srcfd(t_pipeline *pipelines);

static void	open_redirect_srcfd(t_pipeline *pipelines)
{
	t_redirect	*redir;

	if (!pipelines)
		return ;
	redir = pipelines->redirects;
	while (redir)
	{
		if (redir->kind == RD_OUTPUT)
			redir->srcfd = ft_open(redir->path, O_CREAT | O_TRUNC | O_WRONLY,
					0644);
		else if (redir->kind == RD_INPUT)
			redir->srcfd = ft_open(redir->path, O_RDONLY, 0);
		else if (redir->kind == RD_APPEND)
			redir->srcfd = ft_open(redir->path, O_CREAT | O_APPEND | O_WRONLY,
					0644);
		else if (redir->kind == RD_HEREDOC)
			redir->srcfd = read_heredoc(redir->delimiter,
					redir->is_delim_quoted);
		else
			err_exit("Unexpected Redirect kind");
		redir = redir->next;
	}
	open_redirect_srcfd(pipelines->next);
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
	// open redirect path/pipe file descriptors
	open_redirect_srcfd(pipelines);
	rl_event_hook = 0;
	// empty command
	if (pipelines->argv[0] == NULL)
		status = 0;
	else if (g_env.heredoc_interrupted)
	{
		close_redirect_srcfd(pipelines);
		status = 1;
	}
	// builtin && single command
	else if (isbuiltin(pipelines->argv[0]) && pipelines->next == NULL)
	{
		redirect(pipelines->redirects);
		status = exec_builtin(pipelines);
		restore_redirect(pipelines->redirects);
	}
	// multiple command or non-builtin
	else
		status = forkexec_pipeline(pipelines);
	g_env.sig = 0;
	setup_rl();
	return (status);
}
