/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hato <hatopopo142@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:45:21 by hato              #+#    #+#             */
/*   Updated: 2022/12/17 14:03:45 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int	main(void)
{
	printf("ret:%d, errno:%d:%s\n", access("/bin/cat", X_OK), errno, strerror(errno));
	printf("ret:%d, errno:%d:%s\n", access("/bin/cat", X_OK), errno, strerror(errno));
	printf("ret:%d, errno:%d:%s\n", access("/bin/cat", W_OK), errno, strerror(errno));
	printf("ret:%d, errno:%d:%s\n", access("/bin/cat", R_OK), errno, strerror(errno));
	printf("ret:%d, errno:%d:%s\n", access("///bin/cat", X_OK), errno, strerror(errno));
	printf("ret:%d, errno:%d:%s\n", access("/bin////cat", X_OK), errno, strerror(errno));
	printf("ret:%d, errno:%d:%s\n", access("/bin////cat", X_OK), errno, strerror(errno));
	return (0);
}
