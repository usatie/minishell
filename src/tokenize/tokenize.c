/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:25:51 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 18:56:40 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"

static bool		consume_blank(char **rest, char *line);
static t_str	*variable(char **rest, char *line);
static t_str	*special_parameter(char **rest, char *line);
static t_str	*single_quotes(char **rest, char *line);
static t_str	*double_quotes(char **rest, char *line);
static t_str	*plain_text(char **rest, char *line);
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

// echo $USER 
//      ^    ^
// (t_token *) or (t_str *)
//
// echo "hello"$USER"world"
// echo $foo"hello"
// echo "a" "b" "chello"
//
t_str	*variable(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	if (*line != '$')
		fatal_exit("Expected $\n");
	line++;
	if (!is_alpha_under(*line))
		fatal_exit("Expected alphabetic character or underscore.");
	line++;
	while (is_alpha_num_under(*line))
		line++;
	str = new_str(start, line - start, STR_VAR);
	*rest = line;
	return (str);
}

t_str	*special_parameter(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	if (*line != '$')
		fatal_exit("Expected $\n");
	line++;
	if (!is_specialchr(*line))
		fatal_exit("Expected special character.");
	line++;
	str = new_str(start, line - start, STR_SPECIAL_PARAM);
	*rest = line;
	return (str);
}

// Read until next single quote
t_str	*single_quotes(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	line++; // skip the opening quote
	while (*line && *line != '\'')
		line++;
	if (*line != '\'')
	{
		str = new_str(start, line - start, STR_PLAIN);
		*rest = line;
		return (str);
	}
	line++;
	str = new_str(start, line - start, STR_SINGLE);
	*rest = line;
	return (str);
}

// Read until next double quote
// $parameter may be contained
t_str	*double_quotes(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	t_str	paramhead;
	t_str	*param;

	paramhead.next = NULL;
	param = &paramhead;
	start = line;
	line++; // skip the opening quote
	while (*line && *line != '"')
	{
		if (is_variable(line))
		{
			param->next = variable(&line, line);
			param = param->next;
		}
		else if (is_special_param(line))
		{
			param->next = special_parameter(&line, line);
			param = param->next;
		}
		else
			line++;
	}
	if (*line != '"')
	{
		str = new_str(start, line - start, STR_PLAIN);
		*rest = line;
		return (str);
	}
	line++;
	str = new_str(start, line - start, STR_DOUBLE);
	str->parameters = paramhead.next;
	*rest = line;
	return (str);
}

// Read until next punctuator or space
t_str	*plain_text(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	while (*line != '\0' && is_unquoted(line))
		line++;
	if (line - start > 0)
	{
		str = new_str(start, line - start, STR_PLAIN);
		*rest = line;
		return (str);
	}
	fatal_exit("Unexpected character\n");
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
