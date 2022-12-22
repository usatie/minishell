/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:25:23 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:35:42 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_isascii------");
	int	test11 = 0;
	int	test21 = 128;
	int	test31 = '\n';

	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isascii(test11), isascii(test11));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isascii(test21), isascii(test21));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isascii(test31), isascii(test31));
}
*/