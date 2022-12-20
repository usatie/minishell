/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/20 13:55:12 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>

#define PROMPT "minishell $ "

t_env	g_env = {0};

bool	is_syntax_ok(char *cmd)
{
	t_token		*tok;
	t_node		*node;
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		fatal_exit("fork()");
	else if (pid == 0)
	{
		tok = tokenize(cmd);
		node = parse(tok);
		gen_pipeline(node);
		exit(0);
	}
	// parent
	errno = 0;
	if (waitpid(pid, &status, 0) < 0)
	{
		if (errno == EINTR)
			return (128 + SIGINT);
			//status = 1;
		else if (errno == ECHILD)
			status = 0; // ?
		else
			fatal_exit("waitpid()");
	}
	return (status == 0);
}

int	exec(char *cmd)
{
	int			status;
	t_token		*tok;
	t_node		*node;
	t_pipeline	*pipeline;

	if (!is_syntax_ok(cmd))
		return (258);
	// tokenize, parse, ...
	tok = tokenize(cmd);
	node = parse(tok);
	pipeline = gen_pipeline(node);
	g_env.pipeline = pipeline;
	// empty command
	if (pipeline->argv[0] == NULL)
		status = 0;
	// builtin && single command
	else if (isbuiltin(pipeline->argv[0]) && pipeline->next == NULL)
	{
		int		tmpfd;
		tmpfd = -1;
		if (isatty(STDIN_FILENO))
		{
			tmpfd = dup(STDIN_FILENO);
			close(STDIN_FILENO);
		}
		redirect(pipeline);
		status = exec_builtin(pipeline);
		restore_redirect(pipeline);
		if (isatty(tmpfd))
		{
			dup2(tmpfd, STDIN_FILENO);
			close(tmpfd);
		}
	}
	// multiple command or non-builtin
	else
		status = forkexec_pipeline(pipeline);
	//free_all_tok(tok);
	//free_all_node(node);
	//free_all_pipeline(head);
	g_env.pipeline = NULL;
	return (status);
}

int	main(void)
{
	char	*line;

	setup_rl();
	setup_signal();
	setup_term();
	g_env.status = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		g_env.status = exec(line);
		free(line);
	}
	return (g_env.status);
}
