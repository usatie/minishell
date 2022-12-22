/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 02:14:37 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/14 17:52:35 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char sep)
{
	size_t	i;
	size_t	count;
	int	flg;

	i = 0;
	count = 0;
	flg = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sep)
			flg = 0;
		else if (flg == 0)
		{
			flg = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static void	write_word(char *word, char *from, char sep)
{
	size_t	i;

	i = 0;
	while (from[i] != sep && from[i] != '\0')
	{
		word[i] = from[i];
		i++;
	}
	word[i] = '\0';
}

static void	*null_free(char **ans, int wordnum)
{
	while (wordnum > 0)
	{
		wordnum--;
		free(ans[wordnum]);
	}
	free(ans);
	return (NULL);
}

static void	*ft_malloc_word(char **ans, char *str, char sep)
{
	size_t	i;
	size_t	j;
	size_t	wordnum;

	i = 0;
	j = 0;
	wordnum = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sep || str[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (str[i + j] != sep && str[i + j] != '\0')
				j++;
			ans[wordnum] = (char *)malloc(sizeof(char) * (j + 1));
			if (ans[wordnum] == NULL)
				return (null_free(ans, wordnum));
			write_word(ans[wordnum], str + i, sep);
			i += j;
			wordnum++;
		}
	}
	return (ans);
}

char	**ft_split(const char *s, char c)
{
	char	**ans;
	char	*str;
	size_t	num_of_word;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	num_of_word = count_words(str, c);
	ans = (char **)malloc(sizeof(char *) * (num_of_word + 1));
	if (ans == NULL)
		return (NULL);
	ans[num_of_word] = 0;
	ans = ft_malloc_word(ans, str, c);
	if (ans == NULL)
		return (NULL);
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_split------");
	char	s11[] = "     ";
	char	c12 = ' ';
	
//	char	s21[] = "123";
//	char	s22[] = " 56";

	char	**zisaku =  ft_split(s11,c12);
	printf("zisaku\n");
	int i = 0;
	while (zisaku[i] != NULL)
	{
		printf("%s ", zisaku[i]);
		printf("malloc_size : %zu\n", malloc_size(zisaku[i]));
		i++;
	}
	free(zisaku);
}
*/
