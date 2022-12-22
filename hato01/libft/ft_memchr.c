/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:47:02 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/27 14:33:46 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*s_cpy;

	i = 0;
	s_cpy = (char *)s;
	while (i < n)
	{
		if (s_cpy[i] == c)
			return (s_cpy + i);
		i++;
	}
	return (NULL);
}
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_cpy;

	i = 0;
	s_cpy = (unsigned char *)s;
	while (i < n)
	{
		if (s_cpy[i] == (unsigned char)c)
			return ((void *)s_cpy + i);
		i++;
	}
	return (NULL);
}

/*

#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_memchr------");
	char	s11[] = "abcde";
	int	c12 = 258;
	size_t	n13 = 3;
	
	char	s21[] = "test kakuninn akita";
	int	c22 = 'n';
	size_t	n23 = 1;

	printf("zisaku  : %s\n", (char *)ft_memchr(s11,c12,n13));
	printf("library : %s\n\n", (char *)memchr(s11,c12,n13));
	printf("zisaku  : %s\n", (char *)ft_memchr(s21,c22,n23));
	printf("library : %s\n\n", (char *)memchr(s21,c22,n23));
}
*/