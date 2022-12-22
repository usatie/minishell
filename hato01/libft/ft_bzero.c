/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 04:14:45 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/24 18:00:00 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_bzero------");
	char	test11[] = "12345";
	char	test12[] = "12345";
	size_t	test13 = 2;
	ft_bzero(test11,test13);
	bzero(test12,test13);

	char	test21[] = "abcde";
	char	test22[] = "abcde";
	size_t	test23 = 1;
	ft_bzero(test21,test23);
	bzero(test22,test23);

	//char	test31[] = "123\n";

	printf("zisaku  : %s\nlibrary : %s\n\n", test11, test12);
	printf("zisaku  : %s\nlibrary : %s\n\n", test21, test22);
//	printf("zisaku  : %ld\nlibrary : %ld\n\n", ft_strlen(test31), strlen(test31));
}
*/