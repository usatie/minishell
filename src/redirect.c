/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:36:12 by susami            #+#    #+#             */
/*   Updated: 2022/12/17 08:40:38 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include "minishell.h"

static bool	is_valid_fd(int fd);

void	redirect(t_pipeline *command)
{
	t_redirect	*redir;
	int			newfd;

	redir = command->redir_out;
	while (redir)
	{
		// If fd is valid, duplicate it as tmpfd
		if (is_valid_fd(redir->fd))
		{
			redir->tmpfd = redir->fd + 10;
			while (is_valid_fd(redir->tmpfd))
				redir->tmpfd++;
			ft_dup2(redir->fd, redir->tmpfd);
		}
		// open redirirout path and map to out_fd
		newfd = ft_open(redir->path);
		ft_dup2(newfd, redir->fd);
		redir = redir->next;
	}
}

void	restore_redirect(t_pipeline *command)
{
	t_redirect	*redir;

	redir = command->redir_out;
	while (redir)
	{
		if (is_valid_fd(redir->tmpfd))
			ft_dup2(redir->tmpfd, redir->fd);
		else if (redir->tmpfd != redir->fd)
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
