/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:48:46 by susami            #+#    #+#             */
/*   Updated: 2022/12/12 17:14:55 by susami           ###   ########.fr       */
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

size_t	get_envlen(char *name)
{
	char	*value;
	value = getenv(name);
	return (strlen(value));
}

size_t	get_len(t_str *str)
{
	size_t	len;
	t_str	*cur;

	len = 0;
	cur = str;
	while (cur)
	{
		// "hello"
		// 'hello'
		// hello
		// $USER
		len += cur->len;
		if (cur->kind == STR_VAR)
		{
			len -= cur->len;
			char	*name = strndup(cur->pos + 1, cur->len - 1);
			len += get_envlen(name);
		}
		else if (cur->kind == STR_PLAIN)
			;
		else if (cur->kind == STR_DOUBLE)
		{
			len -= 2;
			// "hello $USER"
			for (t_str *var = cur->variables; var; var = var->next)
			{
				len -= var->len;
				char	*name = strndup(var->pos + 1, var->len - 1);
				len += get_envlen(name);
			}
		}
		else if (cur->kind == STR_SINGLE)
			len -= 2;
		else
			err_exit("Unexpected STR type");
		cur = cur->next;
	}
	return (len);
}

char	*convert_to_word(t_str *str)
{
	size_t	len;
	char	*s;
	t_str	*cur;

	len = get_len(str);
	cur = str;
	s = malloc(len + 1);
	if (s == NULL)
		fatal_exit("malloc()");
	len = 0;
	while (cur)
	{
		if (cur->kind == STR_PLAIN)
		{
			memcpy(s + len, cur->pos, cur->len);
			len += cur->len;
		}
		else if (cur->kind == STR_VAR)
		{
			// cur->pos + 1, cur->len - 1
			// $USER
			// shunusami
			char	*name = strndup(cur->pos + 1, cur->len - 1);
			char	*value = getenv(name);
			memcpy(s + len, value, strlen(value));
			len += strlen(value);
		}
		else if (cur->kind == STR_DOUBLE)
		{
			char *p;
			p = cur->pos + 1;
			for (t_str *var = cur->variables; var; var = var->next)
			{
				// plain text
				memcpy(s + len, p, var->pos - p);
				len += var->pos - p;
				// varible expansion
				char	*name = strndup(var->pos + 1, var->len - 1);
				char	*value = getenv(name);
				memcpy(s + len, value, strlen(value));
				p = var->pos + var->len;
				len += strlen(value);
			}
			memcpy(s + len, p, (cur->pos + cur->len - 1) - p);
			len += (cur->pos + cur->len - 1) - p;
			/*
			// "hello $USER world"
			//  ^
			//        ^
			t_str	*var = cur->variables;
			// "hello "
			memcpy(s + len, cur->pos + 1, var->pos - (cur->pos + 1));
			len += var->pos - (cur->pos + 1);
			// "$USER"
			char	*name = strndup(var->pos + 1, var->len - 1);
			char	*value = getenv(name);
			memcpy(s + len, value, strlen(value));
			len += strlen(value);
			// " world"
			memcpy(s + len, var->pos + var->len, (cur->pos + cur->len - 1) - (var->pos + var->len));
			len += (cur->pos + cur->len - 1) - (var->pos + var->len);
			*/
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
