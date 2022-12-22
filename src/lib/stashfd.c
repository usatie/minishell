/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stashfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:18:14 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 21:20:57 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minishell.h"

// Basically, it is the same as dup(), but return value of duplicated fd is
// guaranteed to be greater than or equal to 10.
int	stashfd(int fd)
{
	int	tmpfd;

	if (!is_valid_fd(fd))
	{
		errno = EBADF;
		return (-1);
	}
	tmpfd = fd + 10;
	while (is_valid_fd(tmpfd))
		tmpfd++;
	ft_dup2(fd, tmpfd);
	return (tmpfd);
}
