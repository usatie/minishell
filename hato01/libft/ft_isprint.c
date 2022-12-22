/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:27:09 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:36:33 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (32 <= c && c <= 126);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_isprint------");
	int	test11 = '4';
	int	test21 = 'a';
	int	test31 = '\n';

	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isdigit(test11), isdigit(test11));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isdigit(test21), isdigit(test21));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isdigit(test31), isdigit(test31));
}
*/