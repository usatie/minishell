/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/04 15:30:34 by susami           ###   ########.fr       */
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

#define PROMPT "minishell > "

// find_path("cat") -> "/bin/cat"
char	*find_path(char *cmd)
{
	char	*path;

	path = malloc(PATH_MAX);
	path[0] = '\0';
	if (cmd[0] != '/')
		strcpy(path, "/bin/");
	strcat(path, cmd);
	return (path);
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
	char		*argv[100];
	char		*path;
	t_token		*tok;
	size_t		i;

	tok = tokenize(cmd);
	path = find_path(tok->str);
	i = 0;
	while (tok)
	{
		argv[i] = tok->str;
		i++;
		tok = tok->next;
	}
	argv[i] = NULL;
	child_pid = fork();
	if (child_pid < 0)
		return (-1);
	else if (child_pid == 0)
		execve(path, argv, environ);
	waitpid(child_pid, &status, 0);
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
		if (strcmp(line, "exit") == 0)
			exit(0);
		status = ft_system(line);
		free(line);
	}
	return (status >> 8);
}
