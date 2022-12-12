/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:28:51 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/03 13:25:51 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

/*
ssize_t	write(int fildes, const void *buf, size_t nbyte);_
*/

int	main(void)
{
	char buf[100];
	buf[0] = 'h';
	buf[1] = 'e';
	buf[2] = 'l';
	buf[3] = 'l';
	buf[4] = 'o';
	buf[5] = '\0';

	int fd = 1;

	ssize_t wc = write(fd, buf, 4);

	printf("wc = %zd\n", wc);
}