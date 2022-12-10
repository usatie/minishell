/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/10 19:42:51 by susami           ###   ########.fr       */
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

t_command	*gen_command(t_node *node)
{
	t_command	*command;
	t_node	*elm;
	size_t	i;

	i = 0;
	command = calloc(1, sizeof(t_command));
	if (command == NULL)
		fatal_exit("calloc()");
	elm = node->elements;
	while (elm)
	{
		if (elm->kind == ND_WORD || elm->kind == ND_NUM)
		{
			command->argv[i] = convert_to_word(elm->str);
			i++;
		}
		if (elm->kind == ND_REDIR_OUT)
		{
			command->out_fd = elm->lhs->val;
			command->out_path = convert_to_word(elm->rhs->str);
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
pid_t	fork_and_exec(t_command *command, int inpipe[2], int outpipe[2])
{
	extern char	**environ;
	//int			status;
	pid_t		child_pid;
	int			fdout;

	// Fork and Exec
	child_pid = fork();
	if (child_pid < 0)
		fatal_exit("fork()");
	else if (child_pid == 0)
	{
		// Redirect output
		if (command->out_path)
		{
			fdout = open(command->out_path, O_CREAT | O_WRONLY, 0644);
			if (fdout < 0)
				fatal_exit("open()");
			dup2(fdout, command->out_fd);
		}
		// Find path
		if (command->argv[0] == NULL)
			exit(0);
		command->path = find_path(command->argv[0]);
		if (command->path == NULL)
			err_exit("command not found.\n");
		// Exec
		if (inpipe[1] >= 0 && close(inpipe[1]) < 0) // inpipe's write end won't be used.
			fatal_exit("close()");
		if (outpipe[0] >= 0 && close(outpipe[0]) < 0) // outpipe's read end won't be used.
			fatal_exit("close()");
		if (inpipe[0] != STDIN_FILENO) // dup inpipe's read end to stdin
		{
			if (dup2(inpipe[0], STDIN_FILENO) < 0)
				fatal_exit("dup2()");
			if (close(inpipe[0]) < 0)
				fatal_exit("close()");
		}
		if (outpipe[1] != STDOUT_FILENO) // dup outpipe's write end to stdend
		{
			if (dup2(outpipe[1], STDOUT_FILENO) < 0)
				fatal_exit("dup2()");
			if (close(outpipe[1]) < 0)
				fatal_exit("close()");
		}
		execve(command->path, command->argv, environ);
		fatal_exit("execve()");
	}
	return (child_pid);
}

int	parse_and_exec(char *cmd)
{
	int			status;
	pid_t		child_pid;
	t_node		*node;
	t_node		*start;
	t_command	*command;
	int	inpipe[2] = {STDIN_FILENO, -1};
	int outpipe[2] = {-1, STDOUT_FILENO};

	child_pid = fork();
	if (child_pid < 0)
		err_exit("fork()");
	else if (child_pid == 0)
	{
		// tokenize, parse, ...
		node = parse(cmd);
		start = node;
		while (node->kind == ND_PIPE)
		{
			command = gen_command(node->lhs);
			if (pipe(outpipe) < 0)
				fatal_exit("pipe()");
			node->lhs->pid = fork_and_exec(command, inpipe, outpipe);
			if ((inpipe[0] >= 0 && close(inpipe[0]) < 0)
					|| (inpipe[1] >= 0 && close(inpipe[1]) < 0))
				fatal_exit("close()");
			inpipe[0] = outpipe[0];
			inpipe[1] = outpipe[1];
			node = node->rhs;
		}
		outpipe[0] = -1;
		outpipe[1] = STDOUT_FILENO;
		command = gen_command(node);
		node->pid = fork_and_exec(command, inpipe, outpipe);
		node = start;
		while (node->kind == ND_PIPE)
		{
			if (waitpid(node->lhs->pid, &status, 0) < 0)
				fatal_exit("waitpid()");
			else
				exit(WEXITSTATUS(status));
			node = node->rhs;
		}
		if (waitpid(node->pid, &status, 0) < 0)
			fatal_exit("waitpid()");
		else
			exit(WEXITSTATUS(status));
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
