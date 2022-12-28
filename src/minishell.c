/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/28 14:49:18 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>

#define PROMPT "minishell $ "
#define TOKENIZE_ERROR 258
#define SYNTAX_ERROR 258

t_env		g_env = {};

void	interpret(char *line, int *stat_loc);

int	main(void)
{
	char		*line;

	init_env(&g_env);
	setup_rl();
	setup_signal();
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_env.status);
		free(line);
	}
	return (g_env.status);
}

void	interpret(char *line, int *stat_loc)
{
	t_token		*tok;
	t_node		*node;
	t_pipeline	*pipelines;

	tok = tokenize(line);
	if (g_env.tokenize_error)
		*stat_loc = TOKENIZE_ERROR;
	else if (at_eof(tok))
		*stat_loc = g_env.status;
	else
	{
		node = parse(tok);
		if (g_env.syntax_error)
			*stat_loc = SYNTAX_ERROR;
		else
		{
			expand(node);
			pipelines = gen(node);
			*stat_loc = exec(pipelines);
			free_pipeline(pipelines);
		}
		free_node(node);
	}
	free_tok(tok);
}
