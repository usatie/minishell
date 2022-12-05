/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:13:21 by susami            #+#    #+#             */
/*   Updated: 2022/06/12 09:19:01 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
	1. Why cursize?
	You need to be able to determine the original size of the memory block 
	pointed to by ptr, and there is no portable way to do so.
	
	2. Doesn't shrink?
	It's not required behaviour.
	
	cf.
	https://codereview.stackexchange.com/questions/151019/
*/
void	*ft_reallocf(void *ptr, size_t newsize, size_t cursize)
{
	void	*newptr;

	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return (malloc(newsize));
	else if (newsize <= cursize)
		return (ptr);
	else
	{
		newptr = malloc(newsize);
		if (newptr)
			ft_memmove(newptr, ptr, cursize);
		free(ptr);
		return (newptr);
	}
}
