/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:28:02 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 21:17:57 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
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
