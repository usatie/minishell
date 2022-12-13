/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:48:46 by susami            #+#    #+#             */
/*   Updated: 2022/12/13 10:39:48 by susami           ###   ########.fr       */
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

size_t	get_len(t_str *str)
{
	size_t	len;
	t_str	*cur;

	len = 0;
	cur = str;
	while (cur)
	{
		if (cur->kind == STR_VAR)
			len += cur->value_len;
		else if (cur->kind == STR_PLAIN)
			len += cur->len;
		else if (cur->kind == STR_DOUBLE)
		{
			len += cur->len - 2;
			for (t_str *var = cur->variables; var; var = var->next)
			{
				len -= var->len;
				len += var->value_len;
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
		else if (cur->kind == STR_VAR)
		{
			if (cur->value)
				strncat(s, cur->value, cur->value_len);
		}
		else if (cur->kind == STR_DOUBLE)
		{
			// "hello $USER world"
			char *p;
			p = cur->pos + 1;
			for (t_str *var = cur->variables; var; var = var->next)
			{
				// plain text
				strncat(s, p, var->pos - p);
				// varible expansion
				if (var->value)
					strncat(s, var->value, var->value_len);
				p = var->pos + var->len;
			}
			strncat(s, p, (cur->len - 1) - (p - cur->pos));
		}
		else
			strncat(s, cur->pos + 1, cur->len - 2);
		cur = cur->next;
	}
	return (s);
}
