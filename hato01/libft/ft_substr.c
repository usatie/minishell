/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:30:54 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 20:17:49 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ans;
	size_t	ans_len;

	if (s == NULL)
		return (NULL);
	else if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	else if (start < ft_strlen(s))
	{
		if (start + len <= ft_strlen(s))
			ans_len = len;
		else
			ans_len = ft_strlen(s) - start;
	}
	else
		ans_len = len;
	ans = (char *)malloc(sizeof(char) * (ans_len + 1));
	if (ans == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(ans, s + start, ans_len + 1);
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
	char			s11[] = "tripouille";
	unsigned int	ui12 = 2;
	size_t			len13 = 23;
	
	char			s21[] = "abcde";
	unsigned int	ui22 = 3;
	size_t			len23 = 3;

	char	*ans =  ft_substr(s11,ui12,len13);
	printf("zisaku : %s\n", ans);
	printf("malloc_size : %zu\n\n", malloc_size(ans));
	free(ans);
	
	ans = ft_substr(s21,ui22,len23);
	printf("zisaku : %s\n", ans);
	printf("malloc_size : %zu\n\n", malloc_size(ans));
	free(ans);

	printf("%zu",SIZE_MAX);
}
*/
