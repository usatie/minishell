/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:36:12 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 10:05:13 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include "minishell.h"

static bool	is_valid_fd(int fd);
static void	redirect_output(t_redirect *redir);
static void	redirect_input(t_redirect *redir);
static void	redirect_append(t_redirect *redir);
static void	redirect_heredoc(t_redirect *redir);

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

void	redirect(t_pipeline *command)
{
	t_redirect	*redir;

	redir = command->redirects;
	while (redir)
	{
		if (redir->kind == RD_OUTPUT)
			redirect_output(redir);
		else if (redir->kind == RD_INPUT)
			redirect_input(redir);
		else if (redir->kind == RD_APPEND)
			redirect_append(redir);
		else if (redir->kind == RD_HEREDOC)
			redirect_heredoc(redir);
		else
			err_exit("Unexpected Redirect kind");
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

static void	redirect_output(t_redirect *redir)
{
	int	newfd;

	// If fd is valid, duplicate it as tmpfd
	redir->tmpfd = stashfd(redir->fd);
	// open output path and map to fd
	newfd = ft_open(redir->path, O_CREAT | O_WRONLY, 0644);
	ft_dup2(newfd, redir->fd);
}

static void	redirect_input(t_redirect *redir)
{
	int	newfd;

	// If fd is valid, duplicate it as tmpfd
	redir->tmpfd = stashfd(redir->fd);
	// open input path and map to fd
	newfd = ft_open(redir->path, O_RDONLY, 0);
	ft_dup2(newfd, redir->fd);
}

static void	redirect_append(t_redirect *redir)
{
	int	newfd;

	// If fd is valid, duplicate it as tmpfd
	redir->tmpfd = stashfd(redir->fd);
	// open output path and map to fd
	newfd = ft_open(redir->path, O_CREAT | O_APPEND | O_WRONLY, 0644);
	ft_dup2(newfd, redir->fd);
}

#include <readline/readline.h>

static void	redirect_heredoc(t_redirect *redir)
{
	int	pfd[2];

	// Open pipe
	pipe(pfd);
	// Read from stdin, Write to pipe
	char	*line;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			break;
		}
		if (redir->is_delim_quoted)
			write(pfd[1], line, strlen(line));
		else
			write(pfd[1], line, strlen(line)); // TODO: expand parameters
		write(pfd[1], "\n", 1);
		free(line);
	}
	close(pfd[1]);
	// If fd is valid, duplicate it as tmpfd
	redir->tmpfd = stashfd(redir->fd);
	// open output path and map to fd
	ft_dup2(pfd[0], redir->fd);
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
