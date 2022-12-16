/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 17:07:53 by susami           ###   ########.fr       */
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
	for (t_redirect *red = command->redir_out; red; red = red->next)
	{
		// stash original out_fd
		if (is_valid_fd(red->fd))
			red->dupfd = ft_dup(red->fd);
		// open redirout path and map to out_fd
		fd = ft_open(red->path);
		ft_dup2(fd, red->fd);
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
	
	for (t_redirect *red = command->redir_out; red; red = red->next)
	{
		if (is_valid_fd(red->dupfd))
			ft_dup2(red->dupfd, red->fd);
	}
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
