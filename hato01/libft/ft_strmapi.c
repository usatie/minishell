/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:55:45 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/27 14:16:31 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ans;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ans == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ans[i] = (*f)(i, s[i]);
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>

char ft_test(unsigned int ui, char c)
{
	char	ans;

	ans = ui + c;
	return (ans);
}

int main()
{
	puts("----ft_strmapi------");
	char			s11[] = "abcde";
	unsigned int	ui12 = 12;
	char			c13 = 'a';
	
	//char	s21[] = "123";
	//char	s22[] = " 56";

	char	*ans =  ft_strmapi(s11, (ft_test)(ui12,c13));
	printf("zisaku : %s\n", ans);
	printf("malloc_size : %zu\n\n", malloc_size(ans));
	free(ans);
	
*/