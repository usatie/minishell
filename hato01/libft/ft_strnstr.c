/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 07:40:45 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/14 18:10:51 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (haystack == NULL && len == 0)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while ( i + j < len && haystack[i + j] == needle[j] && needle[j] != '\0')
		{
			if (needle[j + 1] == '\0')
			{
				return (&((char *)haystack)[i]);
			}
			j++;
		}
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
	puts("----ft_strnstr------");

	// char	s21;
	// s21 = NULL;
	// char	s22; 
	// s22 = 2;
	// size_t	n23 = 0;

	// printf("zisaku  : %s\n", ft_strnstr(,s12,n13));
	// printf("library : %s\n\n", strnstr(s11,s12,n13));
//	printf("zisaku  : %s\n", ft_strnstr(NULL,"2",0));
	printf("library : %s\n\n", strnstr(NULL,"2",0));
}
*/