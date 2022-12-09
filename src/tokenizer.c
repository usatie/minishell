#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "minishell.h"

t_str	*new_str(char *pos, size_t len, t_str_kind kind)
{
	t_str	*s;

	s = calloc(sizeof(t_str), 1);
	s->pos = pos;
	s->len = len;
	s->kind = kind;
	return (s);
}

t_token	*new_token(char *pos, size_t len, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
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

t_str	*single_quotes(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	
	start = line;
	line++; // skip the opening quote
	while (*line != '\0' && *line != '\'')
		line++;
	if (*line != '\'')
		err_exit("Unclosed single quote\n");
	line++;
	str = new_str(start, line - start, STR_SINGLE);
	*rest = line;
	return (str);
}

t_str	*double_quotes(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	
	start = line;
	line++; // skip the opening quote
	while (*line != '\0' && *line != '"')
		line++;
	if (*line != '"')
		err_exit("Unclosed single quote\n");
	line++;
	str = new_str(start, line - start, STR_DOUBLE);
	*rest = line;
	return (str);
}

t_str	*plain_text(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	
	start = line;
	while (*line != '\0' && !isspace(*line) && *line != '\'' && *line != '"')
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
		// Identifier
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

