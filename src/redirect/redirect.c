/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:36:12 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 14:34:58 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"

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

void	open_srcfd(t_redirect *redir)
{
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
}

void	close_srcfd(t_redirect *redir)
{
	while (redir)
	{
		close(redir->srcfd);
		redir = redir->next;
	}
}

void	redirect(t_redirect *redir)
{
	while (redir)
	{
		redir->tmpfd = stashfd(redir->fd);
		ft_dup2(redir->srcfd, redir->fd);
		redir = redir->next;
	}
}

void	restore_redirect(t_redirect *redir)
{
	while (redir)
	{
		if (is_valid_fd(redir->tmpfd))
			ft_dup2(redir->tmpfd, redir->fd);
		else if (is_valid_fd(redir->fd))
			ft_close(redir->fd);
		redir = redir->next;
	}
}
