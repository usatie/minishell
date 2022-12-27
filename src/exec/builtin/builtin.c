/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:09:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:47:27 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
		if (ft_strcmp(command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(char **argv)
{
	int		status;
	int		tmpfd;

	// Stash stdin
	tmpfd = stashfd(STDIN_FILENO);
	status = 0;
	if (ft_strcmp(argv[0], "exit") == 0)
		status = ft_exit(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = ft_pwd(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = ft_cd(argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = ft_export(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = ft_env(argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = ft_unset(argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = ft_echo(argv);
	else
		impl_err_exit("exec_builtin", "Unknown Builtin");
	// Restore stdin
	ft_dup2(tmpfd, STDIN_FILENO);
	return (status);
}
