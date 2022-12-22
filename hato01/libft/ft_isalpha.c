/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:04:14 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:32:57 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_isalpha------");
	int	test11 = '4';
	int	test21 = 'a';
	int	test31 = '\n';

	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isalpha(test11), isalpha(test11));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isalpha(test21), isalpha(test21));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isalpha(test31), isalpha(test31));
}
*/