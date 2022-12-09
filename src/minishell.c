/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/09 18:27:44 by susami           ###   ########.fr       */
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

t_command	*gen_command(t_node *node)
{
	t_command	*command;
	t_node	*elm;
	size_t	i;

	i = 0;
	command = calloc(sizeof(t_command), 1);
	elm = node->elements;
	while (elm)
	{
		if (elm->kind == ND_WORD)
		{
			command->argv[i] = convert_to_word(elm->str);
			i++;
		}
		if (elm->kind == ND_REDIRECT_OUTPUT)
		{
			command->out_path = convert_to_word(elm->str);
			command->out_fd = elm->fd;
		}
		elm = elm->next;
	}
	command->argv[i + 1] = NULL;
	return (command);
}

// Return exit status
// The system() function returns the exit status of the shell as returned by 
// waitpid(2), or -1 if an error occurred when invoking fork(2) or waitpid(2). 
// A return value of 127 means the execution of the shell failed.
int	fork_and_exec(t_command *command)
{
	extern char	**environ;
	int			status;
	pid_t		child_pid;
	int			fdout;

	// Redirect output before fork()
	if (command->out_path)
	{
		fdout = open(command->out_path, O_CREAT | O_WRONLY, 0644);
		if (fdout < 0)
			err_exit("open()");
		dup2(fdout, command->out_fd);
	}
	// Find path
	command->path = find_path(command->argv[0]);
	if (command->path == NULL)
		err_exit("command not found.\n");
	// Fork and Exec
	child_pid = fork();
	if (child_pid < 0)
		fatal_exit("fork()");
	else if (child_pid == 0)
	{
		execve(command->path, command->argv, environ);
		fatal_exit("execve()");
	}
	if (waitpid(child_pid, &status, 0) < 0)
		fatal_exit("waitpid()");
	else
		exit(status);
}

t_command	*parse_command(char *cmd)
{
	t_token		*tok;
	t_node		*node;
	t_command	*command;

	tok = tokenize(cmd);
	if (tok == NULL)
		fatal_exit("tokenize()");
	node = parse(tok);
	if (node == NULL)
		fatal_exit("parse()");
	command = gen_command(node);
	if (command == NULL)
		fatal_exit("gen_command()");
	// empty line
	if (command->argv[0] == NULL)
		exit(0);
	return (command);
}

int	parse_and_exec(char *cmd)
{
	int			status;
	pid_t		child_pid;
	t_command	*command;

	child_pid = fork();
	if (child_pid < 0)
		err_exit("fork()");
	else if (child_pid == 0)
	{
		// tokenize, parse, ...
		command = parse_command(cmd);
		fork_and_exec(command);
		exit(127);
	}
	// parent
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
