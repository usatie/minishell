/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:28:02 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 14:36:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
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
