/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:26:12 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/27 12:47:13 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_putchar_fd------");
	char	c11 = 'a';
	char	i12 = 1;
	
	char	c21 = 'b';
	char	i22 = 0;

	ft_putchar_fd(c11, i12);
	printf("\n");
	printf("zisaku : %d\n", c11);
	printf("\n");
	
	ft_putchar_fd(c21, i22);
	printf("\n");
	printf("zisaku : %d\n", c21);
}
*/