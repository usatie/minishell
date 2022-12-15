/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/15 14:30:49 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "minishell.h"

bool	isbuiltin(char *command)
{
	unsigned long		i;
	static const char	*builtins[] = {
//		"echo",
		"cd",
		"pwd",
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

int	ft_pwd(char *argv[])
{
	char	cwd[PATH_MAX];

	(void)argv;
	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

// TODO: bash doesn't follow symlink
// cd /etc
int	ft_cd(char *argv[])
{
	char	*path;

	path = argv[1];
	if (!path)
		path = getenv("HOME");
	if (!path)
	{
		perror("getenv");
		return (1);
	}
	if (chdir(path) < 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	exec_builtin(t_pipeline *pipeline)
{
	char	*command;

	command = pipeline->argv[0];
	if (strcmp(command, "exit") == 0)
		exit(status);
	else if (strcmp(command, "pwd") == 0)
		return (ft_pwd(pipeline->argv));
	else if (strcmp(command, "cd") == 0)
		return (ft_cd(pipeline->argv));
	else
	{
		// TODO
		write(STDERR_FILENO, "Unknown Builtin\n", strlen("Unknown Builtin\n"));
		return (1);
	}
}
