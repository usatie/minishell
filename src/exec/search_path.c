/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:45:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:46:08 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// search_path("cat") -> "/bin/cat"
char	*search_path(char *cmd)
{
	char	*path;
	char	*envpath;
	char	**paths;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = ft_calloc(sizeof(char), PATH_MAX);
	envpath = getenv("PATH");
	paths = ft_split(envpath, ':');
	i = 0;
	while (paths[i])
	{
		strcpy(path, paths[i]);
		strcat(path, "/");
		strcat(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	free(path);
	return (NULL);
}
