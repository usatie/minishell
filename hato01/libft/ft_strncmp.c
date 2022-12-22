/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:18:57 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/27 14:51:13 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
	puts("----ft_strncmp------");
	char	s11[] = "t";
	char	s12[] = "";
	size_t	n13 = 0;
	
	char	s21[] = "";
	char	s22[] = "1";
	size_t	n23 = 0;

	printf("zisaku  : %d\n", ft_strncmp(s11,s12,n13));
	printf("library : %d\n\n", strncmp(s11,s12,n13));
	printf("zisaku  : %d\n", ft_strncmp(s21,s22,n23));
	printf("library : %d\n\n", strncmp(s21,s22,n23));
}
*/