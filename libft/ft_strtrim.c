/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:48:18 by susami            #+#    #+#             */
/*   Updated: 2022/11/18 14:31:17 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*find_head(char const *s, char const *set)
{
	char const	*head;

	head = s;
	while (ft_strchr(set, *head))
		head++;
	return (head);
}

static const char	*find_tail(char const *s, char const *set)
{
	char const	*tail;

	tail = NULL;
	while (*s)
	{
		if (ft_strchr(set, *s) == NULL)
			tail = s;
		s++;
	}
	return (tail);
}


// s1: not protected
// set: not protected
char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*head;
	const char	*tail;
	char		*s;
	
	head = find_head(s1, set);
	tail = find_tail(s1, set);
	if (tail < head)
		ft_strdup("");
	s = ft_substr(s1, head - s1, tail - head + 1);
	return (s);
}
