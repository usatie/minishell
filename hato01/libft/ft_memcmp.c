/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:21:54 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:29:50 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*sa1;
	unsigned char	*sa2;
	int				difference;

	i = 0;
	sa1 = (unsigned char *)s1;
	sa2 = (unsigned char *)s2;
	while (i < n)
	{
		difference = sa1[i] - sa2[i];
		if (difference != 0)
			return (difference);
		i++;
	}
	return (0);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_memcmp------");
	char	s11[] = "abcde";
	char	s12[] = "abcde";
	size_t	n13 = 3;
	
	char	s21[] = "t est kakuninn akita";
	char	s22[] = "t asukete";
	size_t	n23 = 13;

	printf("zisaku  : %d\n", ft_memcmp(s11,s12,n13));
	printf("library : %d\n\n", memcmp(s11,s12,n13));
	printf("zisaku  : %d\n", ft_memcmp(s21,s22,n23));
	printf("library : %d\n\n", memcmp(s21,s22,n23));
}
*/