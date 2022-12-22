/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:25:51 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 11:34:53 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"

static bool		consume_blank(char **rest, char *line);
static t_token	*string(char **rest, char *line);

// "cat -e Makefile"
//  ^   ^  ^

// 'echo "hello"'
//  ^    ^ 
t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		// blank
		if (consume_blank(&line, line))
			continue ;
		// Multi character punctuator
		if (startswith(line, "<<") || startswith(line, ">>"))
		{
			cur->next = new_token(line, 2, TK_PUNCT);
			cur = cur->next;
			line += 2;
			continue ;
		}
		// Single character punctuator
		if (strchr("|<>", *line) != NULL)
		{
			cur->next = new_token(line, 1, TK_PUNCT);
			cur = cur->next;
			line++;
			continue ;
		}
		// Number
		if (is_number(line))
		{
			cur->next = new_token(line, 0, TK_NUM);
			cur = cur->next;
			cur->val = strtol(line, &line, 10);
			cur->len = line - cur->pos;
			cur->str = new_str(cur->pos, cur->len, STR_PLAIN);
			continue ;
		}
		// String
		{
			cur->next = string(&line, line);
			cur = cur->next;
			continue ;
		}
	}
	cur->next = new_token(line, 0, TK_EOF);
	return (head.next);
}

static bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

t_token	*string(char **rest, char *line)
{
	t_token	*tok;
	t_str	head;
	t_str	*cur;

	tok = new_token(line, 0, TK_STRING);
	cur = &head;
	while (*line && !isspace(*line))
	{
		// Single Quotes
		if (*line == '\'')
		{
			cur->next = single_quotes(&line, line);
			cur = cur->next;
			tok->len += cur->len;
			continue ;
		}
		// Double Quotes
		else if (*line == '"')
		{
			cur->next = double_quotes(&line, line);
			cur = cur->next;
			tok->len += cur->len;
			continue ;
		}
		// Special Parameter
		else if (is_special_param(line))
		{
			cur->next = special_parameter(&line, line);
			cur = cur->next;
			tok->len += cur->len;
			continue ;
		}
		// Parameter
		else if (is_variable(line))
		{
			cur->next = variable(&line, line);
			cur = cur->next;
			tok->len += cur->len;
			continue ;
		}
		// Plain text
		else
		{
			cur->next = plain_text(&line, line);
			cur = cur->next;
			tok->len += cur->len;
			continue ;
		}
	}
	tok->str = head.next;
	*rest = line;
	return (tok);
}
