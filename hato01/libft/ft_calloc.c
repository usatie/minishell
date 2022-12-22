/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 09:19:05 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/12 17:43:56 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	mem = malloc(count * size);
	if (mem == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_bzero(mem, count * size);
	return (mem);
}
/*

#include <string.h>
#include <stdio.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_calloc------");
	size_t	test11 = UINT_MAX-1;
	size_t	test12 = UINT_MAX-1;

	size_t	test21 = 2;
	size_t	test22 = 0;

	printf("zisaku  : %zu\n",  malloc_size(ft_calloc(test11, test12)));
	printf("library : %zu\n\n", malloc_size(calloc(test11, test12)));
	printf("zisaku  : %zu\n",  malloc_size(ft_calloc(test21, test22)));
	printf("library : %zu\n\n", malloc_size(calloc(test21, test22)));
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <errno.h>

int main(void) {
	size_t	count = SIZE_MAX/4 + 10;
	size_t	size = sizeof(int);
	int		init_errno = errno;
	char	*lib_ret = calloc(count,size);
	int		lib_errno = errno;

	errno = init_errno;
	char *ft_ret = ft_calloc(count,size);
	int	ft_errno = errno;

	printf("count * size : %zu\n", count * size);
	printf("calloc    malloc_size : %zu\n", malloc_size(lib_ret));
	fprintf(stderr, "errno : %d %s\n", lib_errno, strerror(lib_errno));
	errno = init_errno;
	printf("ft_calloc malloc_size : %zu\n", malloc_size(ft_ret));
	fprintf(stderr, "errno : %d %s\n", ft_errno, strerror(ft_errno));
}
*/