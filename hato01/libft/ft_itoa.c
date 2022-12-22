/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:04:56 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/08 18:09:07 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_longlen(long n)
{
	long	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

static void	ft_put(long n, char *str, int *i)
{
	if (n > 9)
	{
		ft_put(n / 10, str, i);
		ft_put(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*ans;
	int		i;
	long	nbr;

	nbr = n;
	ans = malloc(sizeof(char) * (ft_longlen(nbr) + 1));
	if (ans == NULL)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		ans[i++] = '-';
		nbr *= -1;
	}
	ft_put(nbr, ans, &i);
	ans[i] = '\0';
	return (ans);
}

/*
#include <limits.h>
#include <stdio.h>
int main(void)
{
	puts("----ft_itoa------");
	//printf("s\n", itoa(INT_MAX));
	printf("%s\n", ft_itoa(INT_MAX));
	printf("%s\n", ft_itoa(INT_MIN));
	printf("%s\n", ft_itoa(0));
}
*/