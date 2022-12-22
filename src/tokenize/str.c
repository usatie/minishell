/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:48:46 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 21:51:56 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

// echo "hello"word
// t_str *s1 = "\"hello\""
// t_str *s2 = "world"
// t_str *s3 = "$USER"
// s1->next = s2;
//
// "\"hello\"" -> "hello"
// "world" -> "world"
//
// char *s = "hello world"

t_str	*new_str(t_str_kind kind, char *pos, size_t len, t_str *params)
{
	t_str	*s;

	s = ft_calloc(sizeof(t_str), 1);
	if (s == NULL)
		fatal_exit("ft_calloc()");
	s->pos = pos;
	s->len = len;
	s->kind = kind;
	s->parameters = params;
	return (s);
}

t_str	*add_str_back(t_str *dst, t_str *s)
{
	t_str	*cur;

	if (!dst)
		return (s);
	cur = dst;
	while (cur->next)
		cur = cur->next;
	cur->next = s;
	return (dst);
}

bool	is_any_quoted(t_str *s)
{
	while (s)
	{
		if (s->kind == STR_SINGLE || s->kind == STR_DOUBLE)
			return (true);
		s = s->next;
	}
	return (false);
}
