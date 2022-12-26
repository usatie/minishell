/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:26:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/26 22:18:22 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "minishell.h"

static void	delete_last(char *path);
static void	append(char *dst, char **rest, char *src);
static bool	consume(char **rest, char *path, const char *elem);
static void	setpwd(char *oldpwd, char *path);

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
	char	cwd[PATH_MAX];
	char	*path;
	char	*pwd;

	path = argv[1];
	if (path == NULL)
		path = getenv("HOME");
	if (path == NULL)
	{
		ft_custom_perror("cd", "HOME not set");
		return (1);
	}
	if (chdir(path) < 0)
	{
		ft_perror("cd");
		return (1);
	}
	pwd = getenv("PWD");
	if (pwd)
		ft_setenv("OLDPWD", pwd, 1);
	else
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			ft_perror("getcwd");
			return (1);
		}
		ft_setenv("OLDPWD", cwd, 1);
		pwd = ft_strdup(cwd);
		if (pwd == NULL)
		{
			ft_perror("ft_strdup");
			return (1);
		}
	}
	setpwd(pwd, path);
	return (0);
}

static void	setpwd(char *oldpwd, char *path)
{
	char	newpath[PATH_MAX];

	if (path[0] == '/')
		ft_strlcpy(newpath, "/", PATH_MAX);
	else
		ft_strlcpy(newpath, oldpwd, PATH_MAX);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume(&path, path, "./"))
			;
		else if (ft_strcmp(path, ".") == 0)
			path += 1;
		else if (consume(&path, path, "../"))
			delete_last(newpath);
		else if (ft_strcmp(path, "..") == 0)
		{
			path += 2;
			delete_last(newpath);
		}
		else
			append(newpath, &path, path);
	}
	ft_setenv("PWD", newpath, 1);
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

static void	append(char *dst, char **rest, char *src)
{
	int	len;

	len = 0;
	while (src[len] && src[len] != '/')
		len++;
	if (!endswith(dst, "/"))
		ft_strlcat(dst, "/", PATH_MAX);
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
