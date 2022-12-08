/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/08 23:48:48 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

typedef enum e_node_kind	t_node_kind;
enum e_node_kind {
	ND_STR,
	ND_PLAIN_STR,
	ND_EXPANDABLE,
};

t_command	*new_command(char **argv)
{
	t_command	*command;

	command = calloc(sizeof(t_command), 1);
	command->argv = argv;
	return (command);
}

char	*strjoin_all(t_str *str)
{
	size_t	len;
	char	*s;
	t_str	*cur;

	len = 0;
	cur = str;
	while (cur)
	{
		len += cur->len;
		if (cur->kind != STR_PLAIN)
			len -= 2;
		cur = cur->next;
	}
	cur = str;
	s = malloc(len + 1);
	len = 0;
	while (cur)
	{
		if (cur->kind == STR_PLAIN)
		{
			memcpy(s + len, cur->pos, cur->len);
			len += cur->len;
		}
		else
		{
			memcpy(s + len, cur->pos + 1, cur->len - 2);
			len += cur->len - 2;
		}
		cur = cur->next;
	}
	s[len] = '\0';
	return (s);
}

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
			argv[i] = strjoin_all(tok->str);
			tok = tok->next;
			i++;
		}
	}
	argv[i+1] = NULL;
	return (new_command(argv));
}
