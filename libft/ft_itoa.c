/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:26:16 by susami            #+#    #+#             */
/*   Updated: 2022/04/13 12:20:38 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the size of the string converted from n
// Example.
// get_size(0): 1
// get_size(42: 2
// get_size(-42): 3
static size_t	get_size(int n)
{
	size_t	len;

	len = 0;
	if (n == 0 || n < 0)
		len = 1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		nbr;
	size_t	len;
	char	*s;

	nbr = n;
	len = get_size(n);
	s = ft_calloc(len + 1, sizeof(char));
	if (s == NULL)
		return (NULL);
	while (len--)
	{
		s[len] = (n % 10) + '0';
		if (n < 0)
			s[len] = -(n % 10) + '0';
		n /= 10;
	}
	if (nbr < 0)
		*s = '-';
	return (s);
}
