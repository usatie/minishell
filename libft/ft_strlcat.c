/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:51:04 by susami            #+#    #+#             */
/*   Updated: 2022/04/22 09:53:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;

	if (dstsize == 0 || ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	if (ft_strlen(src) == 0)
		return (ft_strlen(dst));
	cnt = 0;
	while (*dst && cnt < dstsize - 1)
	{
		dst++;
		cnt++;
	}
	while (*src && cnt < dstsize - 1)
	{
		*dst = *src;
		dst++;
		src++;
		cnt++;
	}
	*dst = '\0';
	while (*src++)
		cnt++;
	return (cnt);
}
