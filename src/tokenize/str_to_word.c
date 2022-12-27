/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:51:40 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:19:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool		is_parameter(t_str *s);
static size_t	wordlen(t_str *s, bool expand);
static void		strcat_expanded_double_quote(char *s, t_str *str);
static char		*joinstr(char *s, t_str *str, bool expand);

char	*str_to_word(t_str *str, bool expand)
{
	char	*s;

	s = ft_calloc(wordlen(str, expand) + 1, sizeof(char));
	if (s == NULL)
		fatal_exit("ft_calloc");
	return (joinstr(s, str, expand));
}

static size_t	wordlen(t_str *s, bool expand)
{
	size_t	len;
	t_str	*param;

	if (!s)
		return (0);
	len = wordlen(s->next, expand);
	if (s->kind == STR_PLAIN || (!expand && is_parameter(s)))
		len += s->len;
	else if (s->kind == STR_SINGLE || (!expand && s->kind == STR_DOUBLE))
		len += s->len - 2;
	else if (expand && is_parameter(s))
		len += s->value_len;
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
	return (len);
}

static bool	is_parameter(t_str *s)
{
	if (s->kind == STR_VAR || s->kind == STR_SPECIAL_PARAM)
		return (true);
	return (false);
}

static char	*joinstr(char *s, t_str *str, bool expand)
{
	if (!str)
		return (s);
	if (str->kind == STR_PLAIN || (!expand && is_parameter(str)))
		ft_strncat(s, str->pos, str->len);
	else if (str->kind == STR_SINGLE || (!expand && str->kind == STR_DOUBLE))
		ft_strncat(s, str->pos + 1, str->len - 2);
	else if (expand && is_parameter(str))
		ft_strncat(s, str->value, str->value_len);
	else if (expand && str->kind == STR_DOUBLE)
		strcat_expanded_double_quote(s, str);
	return (joinstr(s, str->next, expand));
}

// Quoted string consists of plain text parts and parameter parts.
// e.g.
//		"hello $USER world" consists of "hello ", "$USER" and " world"
static void	strcat_expanded_double_quote(char *s, t_str *str)
{
	char	*p;
	t_str	*param;

	p = str->pos + 1;
	param = str->parameters;
	while (param)
	{
		// plain text
		ft_strncat(s, p, param->pos - p);
		// parameter expansion
		if (param->value)
			ft_strncat(s, param->value, param->value_len);
		p = param->pos + param->len;
		param = param->next;
	}
	ft_strncat(s, p, (str->len - 1) - (p - str->pos));
}
