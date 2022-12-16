/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 16:54:38 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>

#include "minishell.h"

static bool	is_valid_fd(int fd);

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

int	exec_builtin(t_pipeline *command)
{
	char	*command_name;
	int		status;
	int		fd;

	status = 0;
	command_name = command->argv[0];
	// redirect
	if (command->redir_out)
	{
		// stash original out_fd
		if (is_valid_fd(command->redir_out->fd))
			command->redir_out->dupfd = ft_dup(command->redir_out->fd);
		// open redirout path and map to out_fd
		fd = ft_open(command->redir_out->path);
		ft_dup2(fd, command->redir_out->fd);
	}
	if (strcmp(command_name, "exit") == 0)
		ft_exit(command->argv);
	else if (strcmp(command_name, "pwd") == 0)
		status = ft_pwd(command->argv);
	else if (strcmp(command_name, "cd") == 0)
		status = ft_cd(command->argv);
	else if (strcmp(command_name, "export") == 0)
		status = ft_export(command->argv);
	else if (strcmp(command_name, "env") == 0)
		status = ft_env(command->argv);
	else if (strcmp(command_name, "unset") == 0)
		status = ft_unset(command->argv);
	else if (strcmp(command_name, "echo") == 0)
		status = ft_echo(command->argv);
	else
	{
		write(STDERR_FILENO, "Unknown Builtin\n", strlen("Unknown Builtin\n"));
		status = 1;
	}
	if (command->redir_out && is_valid_fd(command->redir_out->dupfd))
		ft_dup2(command->redir_out->dupfd, command->redir_out->fd);
	return (status);
}

static bool	is_valid_fd(int fd)
{
	struct stat	st;

	if (fd < 0)
		return (false);
	errno = 0;
	if (fstat(fd, &st) < 0 && errno == EBADF)
		return (false);
	return (true);
}
