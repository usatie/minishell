/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:33:29 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 18:37:48 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	while (len > 100)
	{
		write(fd, s, 100);
		s += 100;
		len -= 100;
	}
	write(fd, s, len);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_putstr_fd------");
	char	c11[] = "abc";
	int		i12 = 1;
	
	char	c21[] = "123";
	int		i22 = 0;

	ft_putstr_fd(c11, i12);
	printf("\n");
	printf("zisaku : %s\n", c11);
	printf("\n");
	
	ft_putstr_fd(c21, i22);
	printf("\n");
	printf("zisaku : %s\n", c21);
}
*/