/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 00:08:41 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/14 17:33:41 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	j = ft_strlen(dst);
	dstlen = j;
	srclen = ft_strlen(src);
	if (dstsize > 0 && dstlen < dstsize - 1)
	{
		while (src[i] != '\0' && j < dstsize - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = '\0';
	}
	if (dstlen >= dstsize)
		dstlen = dstsize;
	return (dstlen + srclen);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_strlcat------");
	char	dst11;
	dst11 = NULL;
	
	char	dst12;
	dst12 = NULL;
	char	src13[] = "world";
	size_t	test14 = 0;

	char	dst21[] = "a cdefg";
	char	dst22[] = "a cdefg";
	char	src23[] = "12 3456";
	size_t	test24 = 0;
	
	printf("[zisaku]  return:%ld", ft_strlcat(dst11,src13,test14));
	printf(" dst:%s\n", dst11);
	printf("[library] return:%ld", strlcat(dst12,src13,test14));
	printf(" dst:%s\n\n", dst12);

	printf("[zisaku]  return:%ld", ft_strlcat(dst21,src23,test24));
	printf(" dst:%s\n", dst21);
	printf("[library] return:%ld", strlcat(dst22,src23,test24));
	printf(" dst:%s\n", dst22);
} 
*/