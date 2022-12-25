/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:45:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/25 14:55:22 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "minishell.h"

static bool	is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

static char	*search_x_path(char *cmd, char **paths)
{
	char	*path;
	int		i;

	path = ft_calloc(sizeof(char), PATH_MAX);
	i = 0;
	while (paths[i])
	{
		ft_strlcpy(path, paths[i], PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, cmd, PATH_MAX);
		if (access(path, X_OK) == 0 && is_regular_file(path))
			return (path);
		i++;
	}
	free(path);
	return (NULL);
}

static char	*search_r_path(char *cmd, char **paths)
{
	char	*path;
	int		i;

	path = ft_calloc(sizeof(char), PATH_MAX);
	i = 0;
	while (paths[i])
	{
		ft_strlcpy(path, paths[i], PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, cmd, PATH_MAX);
		if (access(path, R_OK) == 0 && is_regular_file(path))
			return (path);
		i++;
	}
	free(path);
	return (NULL);
}

// search_path("cat") -> "/bin/cat"
char	*search_path(char *cmd)
{
	char	*path;
	char	*envpath;
	char	**paths;

	envpath = getenv("PATH");
	if (envpath == NULL)
		return (NULL);
	paths = ft_split(envpath, ':');
	path = search_x_path(cmd, paths);
	if (path)
		return (path);
	path = search_r_path(cmd, paths);
	if (path)
		return (path);
	return (NULL);
}
