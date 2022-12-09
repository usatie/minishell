/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/09 14:09:46 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

t_node	*new_node(t_node_kind kind, t_token *tok)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->kind = kind;
	node->tok = tok;
	return (node);
}

t_node	*new_node_command(t_node *elements, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_CMD, tok);
	node->elements = elements;
	return (node);
}

bool	equal(t_token *tok, char *op)
{
	return (memcmp(tok->pos, op, tok->len) == 0 && op[tok->len] == '\0');
}

t_token	*skip_kind(t_token *tok, t_token_kind kind)
{
	if (tok->kind != kind)
	{
		printf("Expected %d kind, but got %d kind\n", kind, tok->kind);
		exit(1);
	}
	return (tok->next);
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
//static t_node	*redirection(t_token **rest, t_token *tok);
static t_node	*command_element(t_token **rest, t_token *tok);
static t_node	*command(t_token **rest, t_token *tok);

t_node	*parse(t_token *tok)
{
	return (command(&tok, tok));
}

static t_node	*command(t_token **rest, t_token *tok)
{
	t_node	head;
	t_node	*elm;

	head = (t_node){};
	elm = &head;
	while (tok->kind != TK_EOF)
	{
		elm->next = command_element(&tok, tok);
		elm = elm->next;
	}
	*rest = tok;
	return (new_node_command(head.next, tok));
}

static t_node	*command_element(t_token **rest, t_token *tok)
{
	t_node	*node;

	if (tok->kind == TK_STRING)
	{
		node = new_node(ND_WORD, tok);
		node->str = tok->str;
		*rest = tok->next;
		return (node);
	}
	if (tok->kind == TK_PUNCT)
	{
		if (equal(tok, ">"))
		{
			node = new_node(ND_REDIRECT_OUTPUT, tok);
			tok = tok->next;
			if (tok->kind == TK_STRING)
			{
				node->str = tok->str;
				*rest = tok->next;
				return (node);
			}
		}
	}
	printf("Error\n");
	exit(1);
}
