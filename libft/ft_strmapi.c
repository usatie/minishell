/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 06:59:44 by susami            #+#    #+#             */
/*   Updated: 2022/04/09 16:47:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// s: not protected (difference between "" and NULL is important)
// f: not protected (strmapi should not know about f)
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	new = ft_strdup(s);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (*(new + i))
	{
		*(new + i) = f(i, *(new + i));
		i++;
	}
	return (new);
}
