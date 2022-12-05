/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:05:42 by susami            #+#    #+#             */
/*   Updated: 2022/09/09 22:02:50 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// On 42 VM ubuntu, SIZE_MAX is defined in stdint.h
// #include <limits.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"

/*
DESCRIPTION
The calloc() function contiguously allocates enough space for count objects that
are size bytes of memory each and returns a pointer to the allocated memory.  The
allocated memory is filled with bytes of value zero.

RETURN VALUES
If successful, calloc(), malloc(), realloc(), reallocf(), and valloc() functions
return a pointer to allocated memory.  If there is an error, they return a NULL
pointer and set errno to ENOMEM.

*/
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	if (size > 0 && (SIZE_MAX / size < count))
	{
		errno = ENOMEM;
		return (NULL);
	}
	size *= count;
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}
