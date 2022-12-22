/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 16:24:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>

#define PROMPT "minishell $ "

extern int	_rl_echo_control_chars;
t_env	g_env = {0};

int	interpret(char *line)
{
	int			status;
	t_token		*tok;
	t_node		*node;
	t_pipeline	*pipelines;

	// tokenize, parse, ...
	tok = tokenize(line);
	node = parse(tok);
	pipelines = NULL;
	if (g_env.syntax_error)
		status = 258;
	else
	{
		expand(node);
		pipelines = gen(node);
		status = exec(pipelines);
	}
	free_tok(tok);
	free_node(node);
	free_pipeline(pipelines);
	return (status);
}

int	main(void)
{
	char	*line;

	setup_rl();
	setup_signal();
	_rl_echo_control_chars = 0;
	g_env.status = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		g_env.status = interpret(line);
		free(line);
	}
	return (g_env.status);
}
