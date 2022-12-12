#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
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

bool	consume_space(char **rest, char *line)
{
	if (isspace(*line))
	{
		while (isspace(*line))
			line++;
		*rest = line;
		return (true);
	}
	return (false);
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
// $variable may be contained
t_str	*double_quotes(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	
	start = line;
	line++; // skip the opening quote
	while (*line && *line != '"')
		line++;
	if (*line != '"')
		err_exit("Unclosed single quote\n");
	line++;
	str = new_str(start, line - start, STR_DOUBLE);
	*rest = line;
	return (str);
}

bool	isplain(char c)
{
	return ((strchr("<>|\'\"$", c) == NULL) && (!isspace(c)));
}

// Read until next punctuator or space
t_str	*plain_text(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	
	start = line;
	while (*line != '\0' && isplain(*line))
		line++;
	if (line - start > 0)
	{
		str = new_str(start, line - start, STR_PLAIN);
		*rest = line;
		return (str);
	}
	err_exit("Unexpected character\n");
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
		err_exit("Expected $\n");
	line++;
	if (!isalpha(*line) && *line != '_')
		err_exit("Expected alphabetic character or underscore.");
	line++;
	while (isalpha(*line) || isdigit(*line) || *line == '_')
		line++;
	str = new_str(start, line - start, STR_VAR);
	*rest = line;
	return (str);
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
		else if (*line == '$')
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
		// space
		if (consume_space(&line, line))
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
	return (head.next);
}

