/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/20 22:16:31 by susami           ###   ########.fr       */
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
	int		tmpfd;

	// Stash stdin
	tmpfd = stashfd(STDIN_FILENO);
	// Exec builtin
	status = 0;
	command_name = command->argv[0];
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
	// Restore stdin
	ft_dup2(tmpfd, STDIN_FILENO);
	return (status);
}
