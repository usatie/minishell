/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:35:57 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/12 16:13:35 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
	{
		return (c - ('A' - 'a'));
	}
	return (c);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_tolower------");
	int	test11 = 'A';
	int	test21 = 'a';
	int	test31 = '\n';

	printf("zisaku  : %c\nlibrary : %c\n\n", ft_tolower(test11), tolower(test11));
	printf("zisaku  : %c\nlibrary : %c\n\n", ft_tolower(test21), tolower(test21));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_tolower(test31), tolower(test31));
}
*/