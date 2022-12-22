/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:26:26 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:34:30 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_isdigit------");
	int	test11 = '4';
	int	test21 = 'a';
	int	test31 = '\n';

	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isdigit(test11), isdigit(test11));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isdigit(test21), isdigit(test21));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isdigit(test31), isdigit(test31));
}
*/