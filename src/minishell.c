/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/05 15:44:15 by susami           ###   ########.fr       */
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

t_token	*new_token(char *pos, size_t len, t_token_type type)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
	tok->pos = pos;
	tok->len = len;
	tok->type = type;
	return (tok);
}

// "cat -e Makefile"
//  ^   ^  ^

// 'echo "hello"'
//  ^    ^ 
t_token	*tokenize(char *line)
{
	t_token	*tok;
	size_t	len;

	// skip white space
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (NULL);
	// count len of token
	len = 0;
	// Single character punctuator
	if (strchr("\"'|<>", *line) != NULL)
	{
		tok = new_token(line, 1, TK_PUNCT);
		tok->next = tokenize(line + 1);
	}
	else // Identifier
	{
		while (line[len] && line[len] != ' ' && strchr("\"'|<>", line[len]) == NULL)
			len++;
		tok = new_token(line, len, TK_IDENT);
		tok->next = tokenize(line + len);
	}
	return (tok);
}

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
	char		*argv[100];
	char		*path;
	t_token		*tok;
	size_t		i;

	tok = tokenize(cmd);
	if (tok == NULL)
		return (0);
	// line = " cat -e Makefile"
	// tok->pos = "cat -e Makefile"
	// tok->len = 3
	path = find_path(strndup(tok->pos, tok->len));
	if (path == NULL)
		return (127 << 8);
	i = 0;
	while (tok)
	{
		if (tok->type == TK_PUNCT)
		{
			tok = tok->next;
			continue ;
		}
		argv[i] = strndup(tok->pos, tok->len);
		i++;
		tok = tok->next;
	}
	argv[i] = NULL;
	child_pid = fork();
	if (child_pid < 0)
		return (-1);
	else if (child_pid == 0)
	{
		execve(path, argv, environ);
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
