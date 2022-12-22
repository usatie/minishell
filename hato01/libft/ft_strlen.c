/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:50:38 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/24 17:42:58 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0')
	{
		x++;
	}
	return (x);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_strlen------");
	char	test11[] = "12345";
	char	test21[] = "abcde";
	char	test31[] = "123\n";

	printf("zisaku  : %ld\nlibrary : %ld\n\n", ft_strlen(test11), strlen(test11));
	printf("zisaku  : %ld\nlibrary : %ld\n\n", ft_strlen(test21), strlen(test21));
	printf("zisaku  : %ld\nlibrary : %ld\n\n", ft_strlen(test31), strlen(test31));
}
*/