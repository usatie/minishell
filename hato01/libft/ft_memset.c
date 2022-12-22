/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 04:14:45 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:51:37 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t len)
{
	size_t			i;
	unsigned char	*ans;

	ans = (unsigned char *)buf;
	i = 0;
	while (i < len)
	{
		ans[i] = ch;
		i++;
	}
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_memset------");
	char	test11[] = "12345";
	char	test12[] = "12345";
	int	test13 = '*';
	size_t	test14 = 2;
	ft_memset(test11,test13,test14);
	memset(test12,test13,test14);

	char	test21[] = "abcde";
	char	test22[] = "abcde";
	int	test23 = '1';
	size_t	test24 = 2;
	ft_memset(test21,test23,test24);
	memset(test22,test23,test24);

	//char	test31[] = "123\n";

	printf("zisaku  : %s\nlibrary : %s\n\n", test11, test12);
	printf("zisaku  : %s\nlibrary : %s\n\n", test21, test22);
//	printf("zisaku  : %ld\nlibrary : %ld\n\n", ft_strlen(test31), strlen(test31));
}
*/
