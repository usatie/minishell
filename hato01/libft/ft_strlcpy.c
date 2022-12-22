/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 02:32:47 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 16:10:56 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_strlcpy------");
	char	dst11[] = "12345";
	char	dst12[] = "12345";
	char	src13[] = "";
	size_t	test14 = 2;

	char	dst21[] = "a cdefg";
	char	dst22[] = "a cdefg";
	char	src23[] = "123456";
	size_t	test24 = 5;
	
	printf("[zisaku]  return:%ld", ft_strlcpy(dst11,src13,test14));
	printf(" dst:%s\n", dst11);
	printf("[library] return:%ld", strlcpy(dst12,src13,test14));
	printf(" dst:%s\n\n", dst12);

	printf("[zisaku]  return:%ld", ft_strlcpy(dst21,src23,test24));
	printf(" dst:%s\n", dst21);
	printf("[library] return:%ld", strlcpy(dst22,src23,test24));
	printf(" dst:%s\n", dst22);
}
*/
