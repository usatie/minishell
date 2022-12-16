/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 09:34:35 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

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

int	exec_builtin(t_pipeline *pipeline)
{
	char	*command;
	int		status;

	status = 0;
	command = pipeline->argv[0];
	if (strcmp(command, "exit") == 0)
		ft_exit(pipeline->argv);
	else if (strcmp(command, "pwd") == 0)
		status = ft_pwd(pipeline->argv);
	else if (strcmp(command, "cd") == 0)
		status = ft_cd(pipeline->argv);
	else if (strcmp(command, "export") == 0)
		status = ft_export(pipeline->argv);
	else if (strcmp(command, "env") == 0)
		status = ft_env(pipeline->argv);
	else if (strcmp(command, "unset") == 0)
		status = ft_unset(pipeline->argv);
	else if (strcmp(command, "echo") == 0)
		status = ft_echo(pipeline->argv);
	else
	{
		write(STDERR_FILENO, "Unknown Builtin\n", strlen("Unknown Builtin\n"));
		status = 1;
	}
	return (status);
}
