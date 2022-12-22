/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 01:03:18 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:26:58 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*ans;

	ans = dest;
	if (n == 0 || dest == src)
		return (dest);
	if (src < dest)
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_memmove------");
	char	test11[] = "12345";
	char	test12[] = "12345";
	char	test13[] = "23456";
	size_t	test14 = 2;
	ft_memmove(test11,test13,test14);
	memmove(test12,test13,test14);

	char	test21[] = "abcde";
	char	test22[] = "abcde";
	char	test23[] = "1 3 5";
	size_t	test24 = 4;
	ft_memmove(test21,test23,test24);
	memmove(test22,test23,test24);

	//char	test31[] = "123\n";

	printf("zisaku  : %s\nlibrary : %s\n\n", test11, test12);
	printf("zisaku  : %s\nlibrary : %s\n\n", test21, test22);
//	printf("zisaku  : %ld\nlibrary : %ld\n\n", ft_strlen(test31), strlen(test31));
}
*/