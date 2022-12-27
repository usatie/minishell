/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:55:55 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:08:10 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "minishell.h"

static bool	is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

void	ft_execvp(char *file, char *argv[])
{
	char	*path;

	// Empty command
	if (file == NULL)
		exit(0);
	// Builtin
	if (isbuiltin(file))
		exit(exec_builtin(argv));
	if (file[0] == '.' || file[0] == '/')
		path = file;
	else
		path = search_path(file);
	if (path == NULL || !is_regular_file(path))
		err_exit(file, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(path, "No such file or directory", 127);
	if (access(path, X_OK) < 0)
		err_exit(path, "Permission denied", 126);
	// Execute
	execve(path, argv, g_env.environ);
	fatal_exit(path);
}
