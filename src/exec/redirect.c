/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:36:12 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 12:36:32 by susami           ###   ########.fr       */
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


static int	check_state(void)
{
	if (!g_env.sig)
		return (0);
	g_env.sig = 0;
	g_env.heredoc_interrupted = 1;
	rl_done = 1;
	setup_term();
	return (0);
}

int	read_heredoc(const char *delimiter, bool is_delim_quoted)
{
	char	*line;
	int		pfd[2];

	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	// Open pipe
	pipe(pfd);
	// Read from stdin, Write to pipe
	line = NULL;
	while (!g_env.heredoc_interrupted)
	{
		line = readline("> ");
		if (g_env.heredoc_interrupted)
			break;
		// EOF
		if (!line)
			break;
		// delimiter
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		// Write to pipe
		if (is_delim_quoted)
			write(pfd[1], line, strlen(line));
		else
			write(pfd[1], line, strlen(line)); // TODO: expand parameters
		write(pfd[1], "\n", 1);
		free(line);
	}
	close(pfd[1]);
	setup_rl();
	return (pfd[0]);
}

void	set_srcfd(t_redirect *redir)
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
