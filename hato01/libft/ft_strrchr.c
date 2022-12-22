/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 02:54:42 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/12 16:11:57 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ans;
	size_t	i;

	i = 0;
	ans = NULL;
	while (1)
	{
		if (s[i] == (char)c)
			ans = (char *)(s + i);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_strrchr------");
	char	s11[] = "abcdce";
	int	c12 = 'c';
	
	char	s21[] = "12 345";
	int	c22 = '\0';

	printf("zisaku  : %s\nlibrary : %s\n\n", ft_strrchr(s11,c12), strrchr(s11,c12));
	printf("zisaku  : %s\nlibrary : %s\n\n", ft_strrchr(s21,c22), strrchr(s21,c22));
}
*/