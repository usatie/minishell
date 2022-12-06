#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "minishell.h"

t_token	*new_token(char *pos, size_t len, t_token_type type)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
	tok->pos = pos;
	tok->len = len;
	tok->type = type;
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
	char	*start;

	cur = &head;
	while (*line)
	{
		// space
		while (isspace(*line))
			line++;
		// Single character punctuator
		if (strchr("|<>", *line) != NULL)
		{
			cur->next = new_token(line, 1, TK_PUNCT);
			cur = cur->next;
			continue ;
		}
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
				printf("Error\n");
				exit(1);
			}
			line++;
			cur->next = new_token(start, line - start, TK_SINGLE_QUOTES);
			cur->next->content = strndup(start + 1, line - start - 2); // Exclude quotes
			cur = cur->next;
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
				printf("Error\n");
				exit(1);
			}
			line++;
			cur->next = new_token(start, line - start, TK_DOUBLE_QUOTES);
			cur->next->content = strndup(start + 1, line - start - 2); // Exclude quotes
			cur = cur->next;
			continue ;
		}
		// Identifier
		start = line;
		while (*line != '\0' && !isspace(*line))
			line++;
		if (line - start > 0)
		{
			cur->next = new_token(start, line - start, TK_IDENT);
			cur->next->content = strndup(start, line - start);
			cur = cur->next;
			continue ;
		}
		printf("Error\n");
		exit(1);
	}
	return (head.next);
}

