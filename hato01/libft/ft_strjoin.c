/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:44:11 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/09 22:13:02 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ans;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ans = (char *)malloc(sizeof(char) * len);
	if (ans == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(ans, s1, len);
	ft_strlcat(ans, s2, len);
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_strjoin------");
	char	s11[] = "abcde";
	char	s12[] = "12345";
	
	char	s21[] = "123";
	char	s22[] = " 56";

	char	*ans =  ft_strjoin(s11,s12);
	printf("zisaku : %s\n", ans);
	printf("malloc_size : %zu\n\n", malloc_size(ans));
	free(ans);
	
	ans = ft_strjoin(s21,s22);
	printf("zisaku : %s\n", ans);
	printf("malloc_size : %zu\n\n", malloc_size(ans));
	free(ans);
}
*/