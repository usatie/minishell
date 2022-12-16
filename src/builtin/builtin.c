/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/17 07:43:48 by susami           ###   ########.fr       */
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

void	redirect(t_pipeline *command)
{
	int	newfd;

	for (t_redirect *redir = command->redir_out; redir; redir = redir->next)
	{
		// If fd is valid, duplicate it as tmpfd
		if (is_valid_fd(redir->fd))
		{
			redir->tmpfd = redir->fd + 10;
			while (is_valid_fd(redir->tmpfd))
				redir->tmpfd++;
			ft_dup2(redir->fd, redir->tmpfd);
		}
		// open redirirout path and map to out_fd
		newfd = ft_open(redir->path);
		ft_dup2(newfd, redir->fd);
	}
}

void	restore_redirect(t_pipeline *command)
{
	for (t_redirect *redir = command->redir_out; redir; redir = redir->next)
	{
		if (is_valid_fd(redir->tmpfd))
			ft_dup2(redir->tmpfd, redir->fd);
		else if (redir->tmpfd != redir->fd)
			ft_close(redir->fd);
	}
}

int	exec_builtin(t_pipeline *command)
{
	char	*command_name;
	int		status;

	status = 0;
	command_name = command->argv[0];
	redirect(command);
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
	restore_redirect(command);
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
