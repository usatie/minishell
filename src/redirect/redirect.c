/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:36:12 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 23:17:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

t_redirect	*new_redirect(t_redirect_kind kind, char *word, int fd)
{
	t_redirect	*redirect;

	redirect = calloc(1, sizeof(t_redirect));
	if (!redirect)
		fatal_exit("calloc()");
	redirect->kind = kind;
	if (kind == RD_HEREDOC)
		redirect->delimiter = word;
	else
		redirect->path = word;
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

void	redirect(t_redirect *redir)
{
	while (redir)
	{
		redir->tmpfd = stashfd(redir->fd);
		ft_dup2(redir->srcfd, redir->fd);
		redir = redir->next;
	}
}

// Restore from tail to head
void	restore_redirect(t_redirect *redir)
{
	if (!redir)
		return ;
	restore_redirect(redir->next);
	if (is_valid_fd(redir->tmpfd))
		ft_dup2(redir->tmpfd, redir->fd);
	else if (is_valid_fd(redir->fd))
		ft_close(redir->fd);
}
