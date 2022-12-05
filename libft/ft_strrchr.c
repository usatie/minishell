/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:14:20 by susami            #+#    #+#             */
/*   Updated: 2022/06/01 16:31:27 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	char		ch;

	str = (const char *)s + ft_strlen(s);
	ch = (char)c;
	while (1)
	{
		if (*str == ch)
			return ((char *)str);
		if (str == s)
			return (NULL);
		str--;
	}
}
