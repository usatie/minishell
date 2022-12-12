/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:36:50 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/02 14:06:06 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fd;
	int	pfd[2];
	int	ret;

	fd = open("tmp.txt", O_RDONLY);
	close(2);
	ret = pipe(pfd);
	printf("%d %d \n", pfd[0], pfd[1]);
	printf("%d\n", ret);
	ret = pipe(pfd);
	printf("%d %d \n", pfd[0], pfd[1]);
	printf("%d\n", ret);
	for (int i = -1; i < 10; i++)
	{
		fd = i;
		printf("fd = %d\n", fd);
		errno = 0;
		printf("isatty = %d\n", isatty(fd));
		printf("errno = %d\n\n", errno);
	}
}
