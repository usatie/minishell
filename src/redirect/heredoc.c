/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:01:00 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 15:53:31 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>

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
	char	*expanded_line;
	int		pfd[2];

	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	// Open pipe
	pipe(pfd);
	// Read from stdin, Write to pipe
	while (!g_env.heredoc_interrupted)
	{
		line = readline("> ");
		if (g_env.heredoc_interrupted)
			break ;
		// EOF
		if (!line)
			break ;
		// delimiter
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		// Write to pipe
		if (is_delim_quoted)
			write(pfd[1], line, strlen(line));
		else
		{
			expanded_line = expand_line(line);
			write(pfd[1], expanded_line, strlen(expanded_line));
			free(expanded_line);
		}
		write(pfd[1], "\n", 1);
		free(line);
	}
	close(pfd[1]);
	setup_rl();
	return (pfd[0]);
}
