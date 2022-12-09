/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/09 15:06:46 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

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

t_command	*new_command(char **argv, char *redirect_out)
{
	t_command	*command;

	command = calloc(sizeof(t_command), 1);
	command->argv = argv;
	command->redirect_out = redirect_out;
	return (command);
}

t_command	*gen_command(t_node *node)
{
	char	*argv[100] = {};
	char	*redirect_out = NULL;
	t_node	*elm;
	size_t	i;

	i = 0;
	elm = node->elements;
	while (elm)
	{
		if (elm->kind == ND_WORD)
		{
			argv[i] = convert_to_word(elm->str);
			i++;
		}
		if (elm->kind == ND_REDIRECT_OUTPUT)
		{
			redirect_out = convert_to_word(elm->str);
		}
		elm = elm->next;
	}
	argv[i+1] = NULL;
	return (new_command(argv, redirect_out));
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
	t_command	*command;

	tok = tokenize(cmd);
	if (tok == NULL)
		return (0);
	node = parse(tok);
	command = gen_command(node);
	if (command == NULL)
		return (127 << 8);
	if (command->argv[0] == NULL)
		return (0);
	command->path = find_path(command->argv[0]);
	child_pid = fork();
	if (child_pid < 0)
		return (-1);
	else if (child_pid == 0)
	{
		int fd = open(command->redirect_out, O_WRONLY);
		dup2(fd, STDOUT_FILENO);
		execve(command->path, command->argv, environ);
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
