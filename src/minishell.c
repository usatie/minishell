/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/15 13:35:34 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <errno.h>

#include "minishell.h"

#define PROMPT "minishell $ "

int	status = 0;

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
	if (waitpid(pid, &status, 0) < 0 && errno != ECHILD)
		fatal_exit("waitpid()");
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
	// empty command
	if (pipeline->argv[0] == NULL)
		status = 0;
	// builtin && single command
	else if (isbuiltin(pipeline->argv[0]) && pipeline->next == NULL)
		status = exec_builtin(pipeline);
	// multiple command or non-builtin
	else
		status = forkexec_pipeline(pipeline);
	//free_all_tok(tok);
	//free_all_node(node);
	//free_all_pipeline(head);
	return (status);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		status = exec(line);
		free(line);
	}
	return (status);
}
