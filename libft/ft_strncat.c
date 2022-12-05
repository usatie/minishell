/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:08:56 by susami            #+#    #+#             */
/*   Updated: 2022/08/16 18:15:52 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// strncat
// strlcat
char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s;

	s = s1;
	while (*s)
		s++;
	while (n > 0 && *s2)
	{
		*s = *s2;
		s++;
		s2++;
		n--;
	}
	*s = '\0';
	return (s1);
}
