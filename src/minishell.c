/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/15 13:06:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

#include "libft.h"
#include "minishell.h"

#define PROMPT "minishell $ "

// find_path("cat") -> "/bin/cat"
char	*find_path(char *cmd)
{
	char	*path;
	char	*envpath;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = calloc(sizeof(char), PATH_MAX);
	envpath = getenv("PATH");
	paths = ft_split(envpath, ':');
	for (int i = 0; paths[i]; i++)
	{
		strcpy(path, paths[i]);
		strcat(path, "/");
		strcat(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
	}
	free(path);
	return (NULL);
}

bool	isbuiltin(char *command)
{
	unsigned long		i;
	static const char	*builtins[] = {
//		"echo",
//		"cd",
//		"pwd",
//		"export",
//		"unset",
//		"env",
		"exit"};

	i = 0;
	while (i < sizeof(builtins) / sizeof(*builtins))
	{
		if (strcmp(command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_pipeline *pipeline)
{
	if (strcmp(pipeline->argv[0], "exit") == 0)
		exit(status);
	else
	{
		// TODO
		write(STDERR_FILENO, "Unknown Builtin\n", strlen("Unknown Builtin\n"));
		return (1);
	}
}

int	forkexec_pipeline(t_pipeline *head)
{
	t_pipeline	*pipeline;

	pipeline = head;
	while (pipeline)
	{
		forkexec(pipeline);
		pipeline = pipeline->next;
	}
	// wait all pipeline processes to exit
	pipeline = head;
	while (pipeline)
	{
		if (waitpid(pipeline->pid, &status, 0) < 0 && errno != ECHILD)
			fatal_exit("waitpid()");
		pipeline = pipeline->next;
	}
	return (status);
}

int	parse_and_exec(char *cmd)
{
	int			status;
	t_token		*tok;
	t_node		*node;
	t_pipeline	*pipeline;

	// tokenize, parse, ...
	tok = tokenize(cmd);
	node = parse(tok);

	pipeline = gen_pipeline(node);
	if (pipeline->argv[0] == NULL)
		return (0);
	if (!pipeline->next && isbuiltin(pipeline->argv[0]))
		status = exec_builtin(pipeline);
	else
		status = forkexec_pipeline(pipeline);
	//free_all_tok(tok);
	//free_all_node(node);
	//free_all_pipeline(head);
	return (status);
}

int	status = 0;

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
		status = parse_and_exec(line);
		free(line);
	}
	return (WEXITSTATUS(status));
}
