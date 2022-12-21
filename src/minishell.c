/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 18:50:17 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>

#define PROMPT "minishell $ "

t_env	g_env = {0};

int	exec(char *cmd)
{
	int			status;
	t_token		*tok;
	t_node		*node;
	t_pipeline	*pipelines;

	// tokenize, parse, ...
	tok = tokenize(cmd);
	node = parse(tok);
	pipelines = NULL;
	if (g_env.syntax_error)
		status = 258;
	else
	{
		expand(node);
		pipelines = gen_pipelines(node);
		// open srcfds
		g_env.heredoc_interrupted = 0;
		for (t_pipeline *pl = pipelines; pl; pl = pl->next)
			open_srcfd(pl->redirects);
		g_env.pipeline = pipelines;
		// empty command
		if (pipelines->argv[0] == NULL)
			status = 0;
		else if (g_env.heredoc_interrupted)
		{
			status = 1;
			close_srcfd(pipelines->redirects);
		}
		// builtin && single command
		else if (isbuiltin(pipelines->argv[0]) && pipelines->next == NULL)
		{
			redirect(pipelines->redirects);
			status = exec_builtin(pipelines);
			restore_redirect(pipelines->redirects);
		}
		// multiple command or non-builtin
		else
			status = forkexec_pipeline(pipelines);
	}
	free_tok(tok);
	free_node(node);
	free_pipeline(pipelines);
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
