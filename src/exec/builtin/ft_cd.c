/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:26:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 19:07:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "minishell.h"

static int	getpwd(char *dst, size_t dstsize);
static int	get_cd_target_path(char *dst, size_t dstsize, char *arg);
static void	append_path(char *dst, size_t dstsize, char *path);
static void	delete_last(char *path);
static void	append(char *dst, size_t dstsize, char **rest, char *src);
static bool	consume(char **rest, char *path, const char *elem);

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
	// Initialize newpwd
	if (path[0] == '/')
		ft_strlcpy(newpwd, "/", PATH_MAX);
	else
		ft_strlcpy(newpwd, pwd, PATH_MAX);
	// Append path to newpwd
	append_path(newpwd, PATH_MAX, path);
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

static void	append_path(char *dst, size_t dstsize, char *path)
{
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume(&path, path, "./"))
			;
		else if (ft_strcmp(path, ".") == 0)
			path += 1;
		else if (consume(&path, path, "../"))
			delete_last(dst);
		else if (ft_strcmp(path, "..") == 0)
		{
			path += 2;
			delete_last(dst);
		}
		else
			append(dst, dstsize, &path, path);
	}
}

// Delete the last element of the path
static void	delete_last(char *path)
{
	int	i;
	int	last_slash_idx;

	last_slash_idx = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			last_slash_idx = i;
		i++;
	}
	if (last_slash_idx == 0)
		return ;
	path[last_slash_idx] = '\0';
}

bool	endswith(const char *p, const char *q)
{
	const char	*s1;
	const char	*s2;

	s1 = p;
	s2 = q;
	if (*p == '\0')
		return (*q == '\0');
	while (*p)
		p++;
	while (*q)
		q++;
	while (p != s1 && q != s2)
	{
		if (*p != *q)
			return (false);
		p--;
		q--;
	}
	return (*p == *q);
}

static void	append(char *dst, size_t dstsize, char **rest, char *src)
{
	int	len;

	len = 0;
	while (src[len] && src[len] != '/')
		len++;
	if (!endswith(dst, "/"))
		ft_strlcat(dst, "/", dstsize);
	ft_strncat(dst, src, len);
	*rest = src + len;
}

static bool	consume(char **rest, char *path, const char *elem)
{
	if (ft_strncmp(path, elem, ft_strlen(elem)) == 0)
	{
		*rest = path + ft_strlen(elem);
		return (true);
	}
	return (false);
}
