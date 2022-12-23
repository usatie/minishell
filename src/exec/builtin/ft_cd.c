/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:26:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 21:04:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "minishell.h"

static int	getpwd(char *dst, size_t dstsize);
static int	get_cd_target_path(char *dst, size_t dstsize, char *arg);
void		resolve_filepath(char *dst, size_t dstsize, char *relpath);

/*
cd [-L|-P] [dir]
	  Change the current directory to dir.  The variable HOME is the default
	  dir.  The variable CDPATH defines the search path for the directory
	  containing dir.  Alternative directory names in CDPATH are separated by a
	  colon (:).  A null directory name in CDPATH is the same as the current
	  directory, i.e., ``.''.  If dir begins with a slash (/), then CDPATH is
	  not used. The -P option says to use the physical directory structure
	  instead of following symbolic links (see also the -P option to the set
	  builtin command); the -L option forces symbolic links to be followed.  An
	  argument of - is equivalent to $OLDPWD.  If a non- empty directory name
	  from CDPATH is used, or if - is the first argument, and the directory
	  change is successful, the absolute pathname of the new working directory
	  is written to the standard output.  The return value is true if the
	  directory was successfully changed; false otherwise.
*/
int	ft_cd(char *argv[])
{
	char	path[PATH_MAX];
	char	pwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	if (get_cd_target_path(path, PATH_MAX, argv[1]) < 0)
		return (1);
	if (getpwd(pwd, PATH_MAX) < 0)
		return (1);
	if (chdir(path) < 0)
	{
		ft_perror("cd");
		return (-1);
	}
	if (ft_setenv("OLDPWD", pwd, 1) < 0)
		fatal_exit("ft_setenv");
	if (path[0] == '/')
		ft_strlcpy(newpwd, "/", PATH_MAX);
	else
		ft_strlcpy(newpwd, pwd, PATH_MAX);
	resolve_filepath(newpwd, PATH_MAX, path);
	if (ft_setenv("PWD", newpwd, 1) < 0)
		fatal_exit("ft_setenv");
	return (0);
}

static int	getpwd(char *dst, size_t dstsize)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	pwd = ft_getenv("PWD");
	if (pwd != NULL)
		ft_strlcpy(dst, pwd, dstsize);
	else
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			ft_perror("getcwd");
			return (-1);
		}
		ft_strlcpy(dst, cwd, dstsize);
	}
	return (0);
}

static int	get_cd_target_path(char *dst, size_t dstsize, char *arg)
{
	if (arg == NULL)
	{
		if (ft_getenv("HOME") == NULL)
		{
			ft_custom_perror("cd", "HOME not set");
			return (-1);
		}
		ft_strlcpy(dst, ft_getenv("HOME"), dstsize);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		if (ft_getenv("OLDPWD") == NULL)
		{
			ft_custom_perror("cd", "OLDPWD not set");
			return (-1);
		}
		ft_strlcpy(dst, ft_getenv("OLDPWD"), dstsize);
		ft_putendl_fd(dst, STDOUT_FILENO);
	}
	else
		ft_strlcpy(dst, arg, dstsize);
	return (0);
}
