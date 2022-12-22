/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:02:32 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/26 11:12:31 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_it_c(char c, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ans;
	size_t	i;
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_it_c(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_it_c(s1[end - 1], set))
		end--;
	ans = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (ans == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (start < end)
		ans[i++] = s1[start++];
	ans[i] = 0;
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_substr------");
	char			s11[] = "abcde";
	unsigned int	ui12 = 2;
	size_t			len13 = 4;
	
	char			s21[] = "abcde";
	unsigned int	ui22 = 6;
	size_t			len23 = 0;

	char	*ans =  ft_substr(s11,ui12,len13);
	printf("zisaku : %s\n", ans);
	printf("malloc_size : %zu\n\n", malloc_size(ans));
	free(ans);
	
	ans = ft_substr(s21,ui22,len23);
	printf("zisaku : %s\n", ans);
	printf("malloc_size : %zu\n\n", malloc_size(ans));
	free(ans);
}
*/