/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/06 16:37:07 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

#define PROMPT "minishell > "

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
	for (int i = 0; paths[i]; i++) {
		strcpy(path, paths[i]);
		strcat(path, "/");
		strcat(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
	}
	free(path);
	return (NULL);
}

// Return exit status
// The system() function returns the exit status of the shell as returned by 
// waitpid(2), or -1 if an error occurred when invoking fork(2) or waitpid(2). 
// A return value of 127 means the execution of the shell failed.
int	ft_system(char *cmd)
{
	extern char	**environ;
	int			status;
	pid_t		child_pid;
	t_token		*tok;
	t_node		*node;

	tok = tokenize(cmd);
	if (tok == NULL)
		return (0);
	node = parse(tok);
	if (node == NULL)
		return (127 << 8);
	if (node->cmd == NULL)
		return (0);
	node->path = find_path(node->cmd);
	if (node == NULL)
		return (127 << 8);
	child_pid = fork();
	if (child_pid < 0)
		return (-1);
	else if (child_pid == 0)
	{
		execve(node->path, node->argv, environ);
		exit(127);
	}
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
		status = ft_system(line);
		free(line);
	}
	return (WEXITSTATUS(status));
}
