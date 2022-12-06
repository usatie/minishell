#include <stdlib.h>
#include <string.h>
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
	t_token	*tok;
	size_t	len;

	// skip white space
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (NULL);
	// count len of token
	len = 0;
	// Single character punctuator
	if (strchr("\"'|<>", *line) != NULL)
	{
		tok = new_token(line, 1, TK_PUNCT);
		tok->next = tokenize(line + 1);
	}
	else // Identifier
	{
		while (line[len] && line[len] != ' ' && strchr("\"'|<>", line[len]) == NULL)
			len++;
		tok = new_token(line, len, TK_IDENT);
		tok->next = tokenize(line + len);
	}
	return (tok);
}

