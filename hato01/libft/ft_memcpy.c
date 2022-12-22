/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 04:14:45 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:58:35 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ds;
	unsigned char	*sr;

	ds = (unsigned char *)dst;
	sr = (unsigned char *)src;
	i = 0;
	if (!ds && !sr)
		return (NULL);
	while (i < n)
	{
		ds[i] = sr[i];
		i++;
	}
	return (ds);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_memcpy------");
	char	test11[] = "12345";
	char	test12[] = "12345";
	char	test13[] = "abcde";
	size_t	test14 = 2;
	ft_memcpy(test11,test13,test14);
	memcpy(test12,test13,test14);

	char	test21[] = "abcde";
	char	test22[] = "abcde";
	char	test23[] = "1 3 5";
	size_t	test24 = 4;
	ft_memcpy(test21,test23,test24);
	memcpy(test22,test23,test24);

	//char	test31[] = "123\n";

	printf("zisaku  : %s\nlibrary : %s\n\n", test11, test12);
	printf("zisaku  : %s\nlibrary : %s\n\n", test21, test22);
//	printf("zisaku  : %ld\nlibrary : %ld\n\n", ft_strlen(test31), strlen(test31));
}
*/