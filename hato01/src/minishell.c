/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:14:03 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/23 05:59:33 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_token(char *pos, size_t len)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
	tok->pos = pos;
	tok->len = len;
	return (tok);
}

t_token	*tokenize(char *line)
{
	t_token	*tok;
	size_t	len;

	while (*line == ' ')
		line++;
	len = 0;
	while (line[len] && line[len] != ' ')
		len++;
	if (len == 0)
		return (NULL);
	tok = new_token(line, len);
	tok->next = tokenize(line + len);
	return (tok);
}

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

int	ft_system(char *cmd)
{
	extern char		**environ;
	int				status;
	pid_t			child_pid;
	t_token			*tok;
	char			*argv[100];
	char			*path;
	size_t			i;

	tok = tokenize(cmd);
	if (tok == NULL)
		return 0;
	path = find_path(strndup(tok->pos, tok->len));
	if (path == NULL)
		return (127 << 8);
	i = 0;
	while (tok)
	{
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
