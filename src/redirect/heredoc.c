/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:01:00 by susami            #+#    #+#             */
/*   Updated: 2022/12/24 09:41:01 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

static int	check_state(void);
static bool	break_loop(const char *line, const char *delimiter);
static void	putendl_fd_expand(char *s, int fd, bool expand);

int	read_heredoc(const char *delimiter, bool is_delim_quoted)
{
	char	*line;
	int		pfd[2];

	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	// Open pipe
	if (pipe(pfd) < 0)
		fatal_exit("pipe()");
	// Read from stdin, Write to pipe
	while (!g_env.heredoc_interrupted)
	{
		line = readline("> ");
		if (break_loop(line, delimiter))
		{
			free(line);
			break ;
		}
		// Write to pipe
		putendl_fd_expand(line, pfd[1], !is_delim_quoted);
		free(line);
	}
	close(pfd[1]);
	setup_rl();
	return (pfd[0]);
}

static int	check_state(void)
{
	if (!g_env.sig)
		return (0);
	g_env.sig = 0;
	g_env.heredoc_interrupted = 1;
	rl_done = 1;
	return (0);
}

static bool	break_loop(const char *line, const char *delimiter)
{
	// SIGINT(Ctrl-C)
	if (g_env.heredoc_interrupted)
		return (true);
	// EOF
	if (!line)
		return (true);
	// delimiter
	if (ft_strcmp(line, delimiter) == 0)
		return (true);
	return (false);
}

static void	putendl_fd_expand(char *s, int fd, bool expand)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_line(s);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
