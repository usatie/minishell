/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:28:02 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 21:00:14 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "minishell.h"

int	ft_open(char *path, int oflag, mode_t mode)
{
	int	fd;

	fd = open(path, oflag, mode);
	if (fd < 0)
		err_exit("open()");
	return (fd);
}

void	ft_close(int fd)
{
	if (fd < 0)
		return ;
	if (close(fd) < 0)
		err_exit("close()");
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		err_exit("fork()");
	return (pid);
}

void	ft_dup2(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) < 0)
			err_exit("dup2()");
		ft_close(oldfd);
	}
}

void	internal_unsetenv(char **ep)
{
	char	**sp;

	sp = ep;
	while (*sp)
	{
		*sp = *(sp + 1);
		sp++;
	}
}

int	ft_unsetenv(const char *name)
{
	size_t	len;
	char	**ep;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	len = ft_strlen(name);
	ep = environ;
	while (*ep)
	{
		if (ft_strncmp(*ep, name, len) == 0 && (*ep)[len] == '=')
			internal_unsetenv(ep);
		else
			ep++;
	}
	return (0);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	size_t	size;
	char	*es;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL
		|| value == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (getenv(name) != NULL && overwrite == 0)
		return (0);
	ft_unsetenv(name);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	es = malloc(size);
	if (es == NULL)
		return (-1);
	ft_strlcpy(es, name, size);
	ft_strlcat(es, "=", size);
	ft_strlcat(es, value, size);
	if (ft_putenv(es) < 0)
		return (-1);
	return (0);
}

static int	find_environ_idx(char *name, size_t name_len)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
			break ;
		i++;
	}
	return (i);
}

static int	internal_putenv(char *string, char *name, int i)
{
	if (environ[i])
	{
		free(environ[i]);
		environ[i] = string;
	}
	else
	{
		environ = (char **)ft_reallocf(environ, (i + 2) * sizeof(char *),
				i * sizeof(char *));
		if (environ == NULL)
		{
			free(name);
			return (-1);
		}
		environ[i] = string;
		environ[i + 1] = NULL;
	}
	return (0);
}

int	ft_putenv(char *string)
{
	char	*name_end;
	size_t	name_len;
	char	*name;
	int		idx;

	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		ft_unsetenv(string);
		return (0);
	}
	name_len = name_end - string;
	name = ft_strndup(string, name_len);
	if (name == NULL)
		return (-1);
	idx = find_environ_idx(name, name_len);
	return (internal_putenv(string, name, idx));
}

// Same as dup() but returned fd is assured to be >= 10
int	stashfd(int fd)
{
	int	tmpfd;

	// If fd is invalid, return -1
	if (!is_valid_fd(fd))
	{
		errno = EBADF;
		return (-1);
	}
	// If fd is valid, duplicate it as tmpfd (which is greater than 10)
	tmpfd = fd + 10;
	while (is_valid_fd(tmpfd))
		tmpfd++;
	ft_dup2(fd, tmpfd);
	return (tmpfd);
}

// Return true if there is a open file descriptor
bool	is_valid_fd(int fd)
{
	struct stat	st;

	if (fd < 0)
		return (false);
	errno = 0;
	if (fstat(fd, &st) < 0 && errno == EBADF)
		return (false);
	return (true);
}
