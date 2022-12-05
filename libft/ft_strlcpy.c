/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:33:16 by susami            #+#    #+#             */
/*   Updated: 2022/04/07 16:34:33 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_size;

	if (dstsize == 0)
		return (ft_strlen(src));
	src_size = 0;
	while (*src)
	{
		if (src_size < dstsize - 1)
		{
			*dst = *src;
			dst++;
		}
		src++;
		src_size++;
	}
	*dst = '\0';
	return (src_size);
}
