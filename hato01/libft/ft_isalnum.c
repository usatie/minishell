/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:23:02 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/24 17:33:25 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
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

	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isalnum(test11), isalnum(test11));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isalnum(test21), isalnum(test21));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_isalnum(test31), isalnum(test31));
}
*/