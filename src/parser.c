/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/09 08:53:15 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

typedef struct s_node		t_node;
typedef enum e_node_kind	t_node_kind;
enum e_node_kind {
	ND_WORD,
	ND_CMD_ELEM,
	ND_CMD,
};

struct s_node {
	t_node_kind	kind;
	t_node		*next;
};

t_command	*new_command(char **argv)
{
	t_command	*command;

	command = calloc(sizeof(t_command), 1);
	command->argv = argv;
	return (command);
}

/*
EBNF syntax

redirection       = '>' word
                  | '<' word
			      | '>>' word
			      | '<<' word

command_element   = word
                  | redirection

command           = command_element*
*/
t_node	*redirection(t_token **rest, t_token *tok);
t_node	*command_element(t_token **rest, t_token *tok);
t_node	*command(t_token **rest, t_token *tok);

t_command	*parse(t_token *tok)
{
	char		*argv[100] = {};
	size_t		i;

	// line = " cat -e Makefile"
	// tok->pos = "cat -e Makefile"
	// tok->len = 3
	i = 0;
	while (tok->type != TK_EOF)
	{
		if (tok->type == TK_STRING)
		{
			argv[i] = convert_to_word(tok->str);
			tok = tok->next;
			i++;
		}
	}
	argv[i+1] = NULL;
	return (new_command(argv));
}
