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

t_token	*new_token(char *pos, size_t len, t_token_type type)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
	tok->pos = pos;
	tok->len = len;
	tok->type = type;
	return (tok);
}

bool	startswith(char *p, char *q)
{
	return (memcmp(p, q, strlen(q)) == 0);
}


// "cat -e Makefile"
//  ^   ^  ^

// 'echo "hello"'
//  ^    ^ 
t_token	*tokenize(char *line)
{
	t_token	head = {};
	t_token	*cur;
	char	*start;

	cur = &head;
	while (*line)
	{
		// space
		if (isspace(*line))
		{
			start = line;
			while (isspace(*line))
				line++;
			continue ;
		}
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
		// String
		t_str	sh;
		t_str	*s = &sh;
		cur->next = new_token(line, 0, TK_STRING);
		cur = cur->next;
		while (*line && !isspace(*line))
		{
			// Single Quotes
			if (*line == '\'')
			{
				// echo 'hello'
				// ^    ^
				// tok->pos = "'hello'"
				// tok->content = "hello"
				start = line;
				line++;
				while (*line != '\0' && *line != '\'')
					line++;
				if (*line != '\'')
				{
					printf("Unclosed single quote\n");
					exit(1);
				}
				line++;
				s->next = new_str(start, line - start, STR_SINGLE);
				s = s->next;
				cur->len += s->len;
				continue ;
			}
			// Double Quotes
			if (*line == '"')
			{
				// echo "hello"
				// ^    ^
				// tok->pos = "\"hello""
				// tok->content = "hello"
				start = line;
				line++;
				while (*line != '\0' && *line != '"')
					line++;
				if (*line != '"')
				{
					printf("Unclosed double quote\n");
					exit(1);
				}
				line++;
				s->next = new_str(start, line - start, STR_DOUBLE);
				s = s->next;
				cur->len += s->len;
				continue ;
			}
			// Identifier
			start = line;
			while (*line != '\0' && !isspace(*line) && *line != '\'' && *line != '"')
				line++;
			if (line - start > 0)
			{
				s->next = new_str(start, line - start, STR_PLAIN);
				s = s->next;
				cur->len += s->len;
				continue ;
			}
			printf("Unexpected character\n");
			exit(1);
		}
		cur->str = sh.next;
	}
	cur->next = new_token(line, 0, TK_EOF);
	return (head.next);
}

