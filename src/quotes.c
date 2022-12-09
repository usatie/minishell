/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:48:46 by susami            #+#    #+#             */
/*   Updated: 2022/12/09 08:48:57 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "minishell.h"

char	*convert_to_word(t_str *str)
{
	size_t	len;
	char	*s;
	t_str	*cur;

	len = 0;
	cur = str;
	while (cur)
	{
		len += cur->len;
		if (cur->kind != STR_PLAIN)
			len -= 2;
		cur = cur->next;
	}
	cur = str;
	s = malloc(len + 1);
	len = 0;
	while (cur)
	{
		if (cur->kind == STR_PLAIN)
		{
			memcpy(s + len, cur->pos, cur->len);
			len += cur->len;
		}
		else
		{
			memcpy(s + len, cur->pos + 1, cur->len - 2);
			len += cur->len - 2;
		}
		cur = cur->next;
	}
	s[len] = '\0';
	return (s);
}
