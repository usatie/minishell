/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 06:33:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#include "minishell.h"

int	ft_pwd(char *argv[]);
int	ft_export(char **argv);

bool	isbuiltin(char *command)
{
	unsigned long		i;
	static const char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
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
	char		cwd[PATH_MAX];
	struct stat	st1;
	struct stat	st2;
	char		*pwd;

	(void)argv;
	pwd = getenv("PWD");
	if (pwd)
	{
		bzero(&st1, sizeof(struct stat));
		bzero(&st2, sizeof(struct stat));
		stat(".", &st1);
		stat(pwd, &st2);
		if (st1.st_ino == st2.st_ino)
		{
			printf("%s\n", pwd);
			return (0);
		}
	}
	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

// TODO: bash doesn't follow symlink
// cd /etc
int	ft_cd(char *argv[])
{
	char	cwd[PATH_MAX];
	char	*path;
	char	*pwd;

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
	pwd = getenv("PWD");
	if (pwd)
		setenv("OLDPWD", pwd, 1);
	else if (getcwd(cwd, PATH_MAX))
		setenv("OLDPWD", cwd, 1);
	setenv("PWD", path, 1);
	return (0);
}

int	ft_export(char **argv)
{
	if (putenv(argv[1]) < 0)
		return (1);
	return (0);
}

int	ft_env(char **argv)
{
	(void)argv;
	for (int i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
	return (0);
}

int	ft_unset(char **argv)
{
	if (unsetenv(argv[1]) < 0)
		return (1);
	return (0);
}

int	ft_echo(char **argv)
{
	bool	printnl;
	int		start;

	printnl = true;
	start = 1;
	if (argv[1] && strcmp(argv[1], "-n") == 0)
	{
		printnl = false;
		start = 2;
	}
	for (int i = start; argv[i]; i++)
	{
		if (i > start)
			printf(" ");
		printf("%s", argv[i]);
	}
	if (printnl)
		printf("\n");
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
	else if (strcmp(command, "export") == 0)
		return (ft_export(pipeline->argv));
	else if (strcmp(command, "env") == 0)
		return (ft_env(pipeline->argv));
	else if (strcmp(command, "unset") == 0)
		return (ft_unset(pipeline->argv));
	else if (strcmp(command, "echo") == 0)
		return (ft_echo(pipeline->argv));
	else
	{
		write(STDERR_FILENO, "Unknown Builtin\n", strlen("Unknown Builtin\n"));
		return (1);
	}
}
