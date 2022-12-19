/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:36:12 by susami            #+#    #+#             */
/*   Updated: 2022/12/19 12:38:21 by susami           ###   ########.fr       */
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
		if (redir->kind == REDIR_OUTPUT)
			redirect_output(redir);
		else if (redir->kind == REDIR_INPUT)
			redirect_input(redir);
		else if (redir->kind == REDIR_APPEND)
			redirect_append(redir);
		else if (redir->kind == REDIR_HEREDOC)
			redirect_heredoc(redir);
		else
			err_exit("Unexpected Redirect kind");
		redir = redir->next;
	}
}

static void	redirect_output(t_redirect *redir)
{
	int	newfd;

	// If fd is valid, duplicate it as tmpfd
	if (is_valid_fd(redir->fd))
	{
		redir->tmpfd = redir->fd + 10;
		while (is_valid_fd(redir->tmpfd))
			redir->tmpfd++;
		ft_dup2(redir->fd, redir->tmpfd);
	}
	// open output path and map to fd
	newfd = ft_open(redir->path, O_CREAT | O_WRONLY, 0644);
	ft_dup2(newfd, redir->fd);
}

static void	redirect_input(t_redirect *redir)
{
	int	newfd;

	// If fd is valid, duplicate it as tmpfd
	if (is_valid_fd(redir->fd))
	{
		redir->tmpfd = redir->fd + 10;
		while (is_valid_fd(redir->tmpfd))
			redir->tmpfd++;
		ft_dup2(redir->fd, redir->tmpfd);
	}
	// open input path and map to fd
	newfd = ft_open(redir->path, O_RDONLY, 0);
	ft_dup2(newfd, redir->fd);
}

static void	redirect_append(t_redirect *redir)
{
	int	newfd;

	// If fd is valid, duplicate it as tmpfd
	if (is_valid_fd(redir->fd))
	{
		redir->tmpfd = redir->fd + 10;
		while (is_valid_fd(redir->tmpfd))
			redir->tmpfd++;
		ft_dup2(redir->fd, redir->tmpfd);
	}
	// open output path and map to fd
	newfd = ft_open(redir->path, O_CREAT | O_APPEND | O_WRONLY, 0644);
	ft_dup2(newfd, redir->fd);
}

/*
Here Documents
	This type of redirection instructs the shell to read input from the current
	source until a line containing only word (with no trailing blanks) is seen.
	All of the lines read up to that point are then used as the standard input
	for a command.

	The format of here-documents is:

	<<[-]word here-document delimiter

	No parameter expansion, command substitution, arithmetic expansion, or
	pathname expansion is performed on word.  If any characters in word are
	quoted, the delimiter is the result of quote removal on word, and the lines
	in the here-document are not expanded.  If word is unquoted, all lines of
	the here-document are subjected to parameter expansion, command
	substitution, and arithmetic expansion.  In the latter case, the character
	sequence \<newline> is ignored, and \ must be used to quote the characters
	\, $, and `.

	If the redirection operator is <<-, then all leading tab characters are
	stripped from input lines and the line containing delimiter.  This allows
	here-documents within shell scripts to be indented in a natural fashion.
*/

#include <readline/readline.h>
void	heredoc(t_redirect *redir)
{
	int		pfd[2];
	char	*line;

	if (pipe(pfd) < 0)
		err_exit("pipe()");
	line = NULL;
	while (1)
	{
		if (line)
			write(pfd[1], "\n", 1);
		line = readline("> ");
		if (!line)
			err_exit("EOF while reading heredoc");
		if (strcmp(line, redir->path) == 0)
			break;
		write(pfd[1], line, strlen(line));
		free(line);
	}
	close(pfd[1]);
	redir->heredoc_fd = pfd[0];
}

static void	redirect_heredoc(t_redirect *redir)
{
	heredoc(redir);
	// If fd is valid, duplicate it as tmpfd
	if (is_valid_fd(redir->fd))
	{
		redir->tmpfd = redir->fd + 10;
		while (is_valid_fd(redir->tmpfd))
			redir->tmpfd++;
		ft_dup2(redir->fd, redir->tmpfd);
	}
	// map heredoc fd to fd
	ft_dup2(redir->heredoc_fd, redir->fd);
}

void	restore_redirect(t_pipeline *command)
{
	t_redirect	*redir;

	redir = command->redirects;
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
