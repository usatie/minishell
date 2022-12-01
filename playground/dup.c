/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:32:44 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/01 16:01:40 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int fd = 0;

	fd = open("tmp.txt", O_RDONLY);

	printf("tmp.txt\nfd = %d\n", fd);
	int dup_fd = dup(fd);
	printf("dup_fd = %d\n", dup_fd);
	int dup2_fd = dup2(fd, 121);
	printf("dup2_fd = %d\n", dup2_fd);

	close(fd);
	close(dup_fd);
	close(dup2_fd);
	exit(EXIT_SUCCESS);
}