/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/13 07:11:21 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>
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

int	parse_and_exec(char *cmd)
{
	int			status;
	pid_t		child_pid;
	t_node		*node;

	child_pid = ft_fork();
	if (child_pid == 0)
	{
		// tokenize, parse, ...
		node = parse(cmd);
		t_pipeline	*head;
		t_pipeline	*pipeline;

		head = pipeline = gen_pipeline(node);
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
		exit(WEXITSTATUS(status));
	}
	// wait parse and all pipeline processes to exit
	if (waitpid(child_pid, &status, 0) < 0)
		return (-1);
	else
		return (status);
}

int	main(void)
{
	char	*line;
	int		status;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (strcmp(line, "exit") == 0)
			exit(0);
		status = parse_and_exec(line);
		free(line);
	}
	return (WEXITSTATUS(status));
}
