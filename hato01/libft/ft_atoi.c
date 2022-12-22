/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 08:09:17 by mkunimot          #+#    #+#             */
/*   Updated: 2022/03/12 16:52:23 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isporm(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	ans;
	int		sign;

	i = 0;
	ans = 0;
	sign = 1;
	while (ft_isspace(str[i]) && str[i] != '\0')
		i++;
	if (ft_isporm(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		else if (str[i] == '+')
			sign = 1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return (ans * sign);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_atoi------");
	char	test1[] = "-42";
	char	test2[] = "\t\v\f\r\n \f- \f\t\n\r    6050";
	char	test3[] = "123";
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_atoi(test1), atoi(test1));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_atoi(test2), atoi(test2));
	printf("zisaku  : %d\nlibrary : %d\n\n", ft_atoi(test3), atoi(test3));
}
*/