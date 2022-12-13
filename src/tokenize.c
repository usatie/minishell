/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:25:51 by susami            #+#    #+#             */
/*   Updated: 2022/12/13 12:16:11 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"

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

t_token	*new_token(char *pos, size_t len, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
	if (tok == NULL)
		fatal_exit("calloc()");
	tok->pos = pos;
	tok->len = len;
	tok->kind = kind;
	return (tok);
}

bool	startswith(char *p, char *q)
{
	return (memcmp(p, q, strlen(q)) == 0);
}

/*
`man bash`

DEFINITIONS
	The following definitions are used throughout the rest of this document.
	blank	A space or tab.
	word	A sequence of characters considered as a single unit by the shell.
			Also known as a token.
	name	A word consisting only of alphanumeric characters and underscores,
			and beginning with an alphabetic character or an underscore.  Also 
			referred to as an identifier.
	metacharacter
			A character that, when unquoted, separates words.  One of the
			following:
			|  & ; ( ) < > space tab
	control operator
			A token that performs a control function. It is one of the
			following symbols:
			|| & && ; ;; ( ) | <newline>
*/
static bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

static bool	is_metachr(char c)
{
	//return (strchr("&;()<>", c) || is_blank(c));
	return (strchr("<>", c) || is_blank(c));
}

static bool	is_control_operator(char *s)
{
	return (startswith(s, "&&")
			|| startswith(s, "|")
			|| startswith(s, "\n"));
	//return (startswith(s, "||")
	//		|| startswith(s, "&")
	//		|| startswith(s, "&&")
	//		|| startswith(s, ";")
	//		|| startswith(s, "(")
	//		|| startswith(s, ")")
	//		|| startswith(s, ";;")
	//		|| startswith(s, "|")
	//		|| startswith(s, "\n"));
}

static bool	is_parameter(char *s)
{
	return (*s == '$' && is_alpha_under(s[1]));
}

static bool	is_unquoted(char *s)
{
	return (*s != '\"'
			&& *s != '\''
			&& !is_metachr(*s)
			&& !is_parameter(s)
			&& !is_control_operator(s));
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
t_str	*parameter(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	
	start = line;
	if (*line != '$')
		err_exit("Expected $\n");
	line++;
	if (!is_alpha_under(*line))
		err_exit("Expected alphabetic character or underscore.");
	line++;
	while (is_alpha_num_under(*line))
		line++;
	str = new_str(start, line - start, STR_VAR);
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
		err_exit("Unclosed single quote\n");
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
	t_str	paramhead = {0};
	t_str	*param;
	
	param = &paramhead;
	start = line;
	line++; // skip the opening quote
	while (*line && *line != '"')
	{
		if (is_parameter(line))
		{
			param->next = parameter(&line, line);
			param = param->next;
		}
		else
			line++;
	}
	if (*line != '"')
		err_exit("Unclosed single quote\n");
	line++;
	str = new_str(start, line - start, STR_DOUBLE);
	str->variables = paramhead.next;
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
	err_exit("Unexpected character\n");
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
		// Parameter
		else if (*line == '$' && is_alpha_under(line[1]))
		{
			cur->next = parameter(&line, line);
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

// "cat -e Makefile"
//  ^   ^  ^

// 'echo "hello"'
//  ^    ^ 
t_token	*tokenize(char *line)
{
	t_token	head = {};
	t_token	*cur;

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
		if (isdigit(*line))
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
	expand_parameter(head.next);
	return (head.next);
}

