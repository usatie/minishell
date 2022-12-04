/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:21:05 by susami            #+#    #+#             */
/*   Updated: 2022/12/04 14:35:40 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "minishell > "

// line = " exit  | echo   'hello' >out "
// tok1.str ^
// tok1.len 4
// tok1.next tok2
//
// tok2           ^
// tok2.len 1
// tok2.next tok3
//
// tok3             ^
// tok3.len 4
// tok3.next tok4
//
// ...
//
// lexer/tokenizer  : {"exit", "|", "echo", "'hello'"}
// parser           : { {"cmd" : "exit", "argv": {"exit", NULL}, ""....},
//                      {"cmd" : "echo", "argv": {"echo", "'hello'", NULL},
//                      "1": "out", "0": "stdin", "2": "stderr"} }

typedef struct s_token	t_token;

struct s_token {
	char	*str;
	size_t	len;
	t_token	*next;
};

t_token	*new_token(char *str, size_t len)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
	tok->str = str;
	tok->len = len;
	return (tok);
}

t_token	*tokenize(char *line);

t_token	*tokenize(char *line)
{
	t_token	*tok;
	size_t	len;

	while (*line == ' ')
		line++;
	len = 0;
	while (line[len] != ' ' && line[len] != '\0')
		len++;
	if (len == 0)
		return (NULL);
	tok = new_token(line, len);
	tok->next = tokenize(line + len);
	return (tok);
}

int	main(void)
{
	char	*line;
	int		status;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		t_token	*tok = tokenize(line);
		while (tok)
		{
			printf("[%s], %zu\n", tok->str, tok->len);
			tok = tok->next;
		}
		if (strcmp(line, "exit") == 0)
			exit(0);
		status = system(line);
		free(line);
	}
	return (status >> 8);
}
