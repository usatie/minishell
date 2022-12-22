/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:02:50 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/09 22:00:59 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ans;
	size_t	i;

	i = 0;
	ans = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ans == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
/*
#include <string.h>
#include <stdio.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_strdup------");
	//(size_t)-1 の文字数のstringが欲しい、、、
	char	test11[] = "a";
	char	test21[] = "1234567890";

	printf("zisaku  : %s\n",  ft_strdup(test11));
	printf("library : %s\n\n", strdup(test11));
	printf("zisaku  : %s\n",  ft_strdup(test21));
	printf("library : %s\n\n", strdup(test21));
}
*/