/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:41:09 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 15:43:14 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		if (s[i] == '\0')
			break ;
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
	puts("----ft_strchr------");
	char	s11[] = "abcde";
	int	c12 = 'c';
	
	char	s21[] = "12 345";
	int	c22 = '\0';

	printf("zisaku  : %s\nlibrary : %s\n\n", ft_strchr(s11,c12), strchr(s11,c12));
	printf("zisaku  : %s\nlibrary : %s\n\n", ft_strchr(s21,c22), strchr(s21,c22));
}
*/