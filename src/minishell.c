/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/28 07:50:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>

#define PROMPT "minishell $ "

t_env		g_env = {};

// Never return NULL
char	**environ_dup(void)
{
	extern char	**environ;
	char		**dup;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (dup == NULL)
		fatal_exit("ft_calloc");
	i = 0;
	while (environ[i])
	{
		dup[i] = ft_strdup(environ[i]);
		if (dup[i] == NULL)
			fatal_exit("ft_strdup");
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->environ_name = ft_calloc(1, sizeof(char *));
	if (e->environ_name == NULL)
		fatal_exit("ft_calloc");
	e->environ = environ_dup();
}

#define TOKENIZE_ERROR 258
#define SYNTAX_ERROR 258

void	newinterpret(char *line, int *stat_loc)
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

int	interpret(char *line)
{
	int			status;
	t_token		*tok;
	t_node		*node;
	t_pipeline	*pipelines;

	// tokenize, parse, ...
	tok = tokenize(line);
	node = parse(tok);
	if (at_eof(tok))
		status = g_env.status;
	else if (g_env.syntax_error)
		status = 258;
	else
	{
		expand(node);
		pipelines = gen(node);
		status = exec(pipelines);
		free_pipeline(pipelines);
	}
	free_tok(tok);
	free_node(node);
	return (status);
}

int	main(void)
{
	char		*line;

	init_env(&g_env);
	setup_rl();
	setup_signal();
	g_env.status = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		newinterpret(line, &g_env.status);
		free(line);
	}
	return (g_env.status);
}
