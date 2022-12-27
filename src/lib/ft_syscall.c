/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:28:02 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:21:31 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "minishell.h"

void	ft_close(int fd)
{
	if (fd < 0)
		return ;
	if (close(fd) < 0)
		fatal_exit("close");
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		fatal_exit("fork");
	return (pid);
}

void	ft_dup2(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) < 0)
			fatal_exit("dup2");
		ft_close(oldfd);
	}
}
