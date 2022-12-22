/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:11:38 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/10 18:41:31 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	if (nb < 10)
		ft_putchar_fd(nb + '0', fd);
}

/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc/malloc.h>
int main()
{
	puts("----ft_putnbr_fd------");
	int	i11 = 12;
	int	i12 = 12;
	
	int	i21 = 1234;
	int	i22 = 13;

	ft_putnbr_fd(i11, i12);
	printf("\n");
	printf("zisaku : %d\n", i11);
	printf("\n");
	
	ft_putnbr_fd(i21, i22);
	printf("\n");
	printf("zisaku : %d\n", i21);
}
*/