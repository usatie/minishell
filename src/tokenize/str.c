/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:48:46 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 23:25:24 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
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

t_str	*new_str(char *pos, size_t len, t_str_kind kind)
{
	t_str	*s;

	s = calloc(sizeof(t_str), 1);
	if (s == NULL)
		fatal_exit("calloc()");
	s->pos = pos;
	s->len = len;
	s->kind = kind;
	return (s);
}

size_t	get_len(t_str *str)
{
	size_t	len;
	t_str	*cur;

	len = 0;
	cur = str;
	while (cur)
	{
		if (cur->kind == STR_VAR || cur->kind == STR_SPECIAL_PARAM)
			len += cur->value_len;
		else if (cur->kind == STR_PLAIN)
			len += cur->len;
		else if (cur->kind == STR_DOUBLE)
		{
			len += cur->len - 2;
			for (t_str *param = cur->parameters; param; param = param->next)
			{
				len -= param->len;
				len += param->value_len;
			}
		}
		else if (cur->kind == STR_SINGLE)
			len += cur->len - 2;
		else
			err_exit("Unexpected STR type");
		cur = cur->next;
	}
	return (len);
}

char	*convert_to_word(t_str *str)
{
	char	*s;
	t_str	*cur;

	cur = str;
	s = calloc(get_len(str) + 1, sizeof(char));
	if (s == NULL)
		fatal_exit("malloc()");
	while (cur)
	{
		if (cur->kind == STR_PLAIN)
			strncat(s, cur->pos, cur->len);
		else if (cur->kind == STR_VAR || cur->kind == STR_SPECIAL_PARAM)
		{
			if (cur->value)
				strncat(s, cur->value, cur->value_len);
		}
		else if (cur->kind == STR_DOUBLE)
		{
			// "hello $USER world"
			char	*p;
			p = cur->pos + 1;
			for (t_str *param = cur->parameters; param; param = param->next)
			{
				// plain text
				strncat(s, p, param->pos - p);
				// paramible expansion
				if (param->value)
					strncat(s, param->value, param->value_len);
				p = param->pos + param->len;
			}
			strncat(s, p, (cur->len - 1) - (p - cur->pos));
		}
		else
			strncat(s, cur->pos + 1, cur->len - 2);
		cur = cur->next;
	}
	return (s);
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
