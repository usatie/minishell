/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:26:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 09:26:22 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "minishell.h"

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