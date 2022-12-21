/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:36:12 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 14:07:56 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include "minishell.h"
#include <readline/readline.h>

static bool	is_valid_fd(int fd);

t_redirect	*new_redirect(t_redirect_kind kind, char *path, int fd)
{
	t_redirect	*redirect;

	redirect = calloc(1, sizeof(t_redirect));
	if (!redirect)
		fatal_exit("calloc()");
	redirect->kind = kind;
	redirect->path = path;
	redirect->fd = fd;
	redirect->tmpfd = -1;
	return (redirect);
}

t_redirect	*add_redir_back(t_redirect *head, t_redirect *new_redir)
{
	t_redirect	*cur;
	
	if (!head)
		return (new_redir);
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_redir;
	return (head);
}

void	open_srcfd(t_pipeline *pipeline)
{
	t_redirect	*redir;

	while (pipeline)
	{
		redir = pipeline->redirects;
		while (redir)
		{
			if (redir->kind == RD_OUTPUT)
				redir->srcfd = ft_open(redir->path, O_CREAT | O_WRONLY, 0644);
			else if (redir->kind == RD_INPUT)
				redir->srcfd = ft_open(redir->path, O_RDONLY, 0);
			else if (redir->kind == RD_APPEND)
				redir->srcfd = ft_open(redir->path, O_CREAT | O_APPEND | O_WRONLY, 0644);
			else if (redir->kind == RD_HEREDOC)
				redir->srcfd = read_heredoc(redir->delimiter, redir->is_delim_quoted);
			else
				err_exit("Unexpected Redirect kind");
			redir = redir->next;
		}
		pipeline = pipeline->next;
	}
}

void	close_srcfd(t_pipeline *pipeline)
{
	t_redirect	*redir;

	while (pipeline)
	{
		redir = pipeline->redirects;
		while (redir)
		{
			close(redir->srcfd);
			redir = redir->next;
		}
		pipeline = pipeline->next;
	}
}

void	redirect(t_pipeline *command)
{
	t_redirect	*redir;

	redir = command->redirects;
	while (redir)
	{
		redir->tmpfd = stashfd(redir->fd);
		ft_dup2(redir->srcfd, redir->fd);
		redir = redir->next;
	}
}

// Same as dup() but returned fd is assured to be >= 10
int	stashfd(int fd)
{
	int	tmpfd;

	// If fd is invalid, return -1
	if (!is_valid_fd(fd))
	{
		errno = EBADF;
		return (-1);
	}
	// If fd is valid, duplicate it as tmpfd (which is greater than 10)
	tmpfd = fd + 10;
	while (is_valid_fd(tmpfd))
		tmpfd++;
	ft_dup2(fd, tmpfd);
	return (tmpfd);
}

void	restore_redirect(t_pipeline *command)
{
	t_redirect	*redir;

	redir = command->redirects;
	while (redir)
	{
		if (is_valid_fd(redir->tmpfd))
			ft_dup2(redir->tmpfd, redir->fd);
		else if (is_valid_fd(redir->fd))
			ft_close(redir->fd);
		redir = redir->next;
	}
}

static bool	is_valid_fd(int fd)
{
	struct stat	st;

	if (fd < 0)
		return (false);
	errno = 0;
	if (fstat(fd, &st) < 0 && errno == EBADF)
		return (false);
	return (true);
}
