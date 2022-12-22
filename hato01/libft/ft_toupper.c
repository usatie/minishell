/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:29:41 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:37:57 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
	{
		return (c + ('A' - 'a'));
	}
	return (c);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_toupper------");
	int	test11 = 'A';
	int	test21 = 'a';
	int	test31 = '\n';

	printf("zisaku  : %c\nlibrary : %c\n\n", ft_toupper(test11), toupper(test11));
	printf("zisaku  : %c\nlibrary : %c\n\n", ft_toupper(test21), toupper(test21));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_toupper(test31), toupper(test31));
}
*/