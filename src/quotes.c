/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:48:46 by susami            #+#    #+#             */
/*   Updated: 2022/12/12 16:03:30 by susami           ###   ########.fr       */
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
char	*convert_to_word(t_str *str)
{
	size_t	len;
	char	*s;
	t_str	*cur;

	len = 0;
	cur = str;
	while (cur)
	{
		if (cur->kind == STR_VAR)
		{
			char	*name = strndup(cur->pos + 1, cur->len - 1);
			char	*value = getenv(name);
			len += strlen(value);
		}
		else if (cur->kind == STR_PLAIN)
			len += cur->len;
		else if (cur->kind == STR_DOUBLE && cur->variables)
		{
			//  + len("hello $USER") - len("")
			len += cur->len - 2;

			// + len(getenv("USER")) - len($USER)
			t_str	*var = cur->variables;
			char	*name = strndup(var->pos + 1, var->len - 1);
			char	*value = getenv(name);
			len += strlen(value);
			len -= var->len;
		}
		else
			len += cur->len - 2;
		cur = cur->next;
	}
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
		else if (cur->kind == STR_DOUBLE && cur->variables)
		{
			// "hello $USER world"
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
