/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:02:49 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 18:40:10 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_putendl_fd------");
	char	c11[] = "abc";
	int	i12 = 1;
	
	char	c21[] = "123";
	int	i22 = 0;

	ft_putendl_fd(c11, i12);
	printf("\n");
	printf("zisaku : %s\n", c11);
	printf("\n");
	
	ft_putendl_fd(c21, i22);
	printf("\n");
	printf("zisaku : %s\n", c21);
}
*/