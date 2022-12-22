/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:48:46 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 10:12:43 by susami           ###   ########.fr       */
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

static bool	is_parameter(t_str *s)
{
	if (s->kind == STR_VAR || s->kind == STR_SPECIAL_PARAM)
		return (true);
	return (false);
}

static size_t	wordlen(t_str *s, bool expand)
{
	size_t	len;
	t_str	*param;

	if (!s)
		return (0);
	len = wordlen(s->next, expand);
	if (s->kind == STR_PLAIN)
		len += s->len;
	else if (s->kind == STR_SINGLE)
		len += s->len - 2;
	else if (!expand && is_parameter(s))
		len += s->len;
	else if (expand && is_parameter(s))
		len += s->value_len;
	else if (!expand && s->kind == STR_DOUBLE)
		len += s->len - 2;
	else if (expand && s->kind == STR_DOUBLE)
	{
		len += s->len - 2;
		param = s->parameters;
		while (param)
		{
			len -= param->len;
			len += param->value_len;
			param = param->next;
		}
	}
	else
		err_exit("Unexpected STR type");
	return (len);
}

static char	*joinstr(char *s, t_str *str, bool expand)
{
	char	*p;
	t_str	*param;

	if (!str)
		return (s);
	if (str->kind == STR_PLAIN)
		strncat(s, str->pos, str->len);
	else if (str->kind == STR_SINGLE)
		strncat(s, str->pos + 1, str->len - 2);
	else if (!expand && is_parameter(str))
		strncat(s, str->pos, str->len);
	else if (expand && is_parameter(str))
		strncat(s, str->value, str->value_len);
	else if (!expand && str->kind == STR_DOUBLE)
		strncat(s, str->pos + 1, str->len - 2);
	else if (expand && str->kind == STR_DOUBLE)
	{
		// "hello $USER world"
		p = str->pos + 1;
		param = str->parameters;
		while (param)
		{
			// plain text
			strncat(s, p, param->pos - p);
			// parameter expansion
			if (param->value)
				strncat(s, param->value, param->value_len);
			p = param->pos + param->len;
			param = param->next;
		}
		strncat(s, p, (str->len - 1) - (p - str->pos));
	}
	else
		err_exit("Unexpected STR type");
	return (joinstr(s, str->next, expand));
}

char	*str_to_word(t_str *str, bool expand)
{
	char	*s;

	s = calloc(wordlen(str, expand) + 1, sizeof(char));
	if (s == NULL)
		fatal_exit("malloc()");
	return (joinstr(s, str, expand));
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
