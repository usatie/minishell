/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/14 16:15:48 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

t_node	*new_node(t_node_kind kind, t_token *tok)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	if (node == NULL)
		fatal_exit("calloc()");
	node->kind = kind;
	node->tok = tok;
	return (node);
}

t_node	*new_node_binary(t_node_kind kind, t_node *lhs, t_node *rhs, t_token *tok)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	if (node == NULL)
		fatal_exit("calloc()");
	node->lhs = lhs;
	node->rhs = rhs;
	node->kind = kind;
	node->tok = tok;
	return (node);
}

t_node	*new_node_num(long val, t_token *tok)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	if (node == NULL)
		fatal_exit("calloc()");
	node->kind = ND_NUM;
	node->val = val;
	node->tok = tok;
	return (node);
}

bool	equal(t_token *tok, char *op)
{
	return (memcmp(tok->pos, op, tok->len) == 0 && op[tok->len] == '\0');
}

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

/*
EBNF syntax

redirection       = num? '>' word
                  | num? '<' word
			      | num? '>>' word
			      | num? '<<' word

command           = (redirection | word)*

pipeline          = command ('|' pipeline)*
*/
static t_node	*num(t_token **rest, t_token *tok);
static t_node	*word(t_token **rest, t_token *tok);
static t_node	*redirection(t_token **rest, t_token *tok);
static t_node	*command(t_token **rest, t_token *tok);
static t_node	*pipeline(t_token **rest, t_token *tok);

t_node	*parse(t_token *tok)
{
	return (pipeline(&tok, tok));
}

// pipeline = command ('|' pipeline)*
static t_node	*pipeline(t_token **rest, t_token *tok)
{
	t_token	*start;
	t_node	*node;

	node = command(&tok, tok);
	if (equal(tok, "|"))
	{
		start = tok;
		node = new_node_binary(ND_PIPE, node, pipeline(&tok, tok->next), start);
	}
	*rest = tok;
	return (node);
}

// command = command_element*
static t_node	*command(t_token **rest, t_token *tok)
{
	t_node	*cmd;
	t_node	head;
	t_node	*arg;

	cmd = new_node(ND_CMD, tok);
	head = (t_node){};
	arg = &head;
	while (!at_eof(tok) && !equal(tok, "|"))
	{
		// '>' word | num '>' word
		if (equal(tok, ">") || (tok->kind == TK_NUM && equal(tok->next, ">")))
		{
			cmd->redir_out = redirection(&tok, tok);
			continue ;
		}
		// word
		else if (tok->kind == TK_STRING)
		{
			cmd->nargs++;
			arg->next = word(&tok, tok);
			arg = arg->next;
			continue ;
		}
		// num
		else if (tok->kind == TK_NUM)
		{
			cmd->nargs++;
			arg->next = num(&tok, tok);
			arg = arg->next;
			continue ;
		}
		err_exit("Invalid token for <command_element>");
	}
	cmd->args = head.next;
	*rest = tok;
	return (cmd);
}

// redirection = num? '>' word
//             | num? '<' word
//             | num? '<<' word
//             | num? '>>' word
static t_node	*redirection(t_token **rest, t_token *tok)
{
	t_node	*node;

	// num?
	node = NULL;
	if (tok->kind == TK_NUM)
		node = num(&tok, tok);
	// '>' word
	if (equal(tok, ">"))
	{
		if (node == NULL)
			node = new_node_num(STDOUT_FILENO, tok);
		node = new_node_binary(ND_REDIR_OUT, node, word(rest, tok->next), tok);
		return (node);
	}
	// '<' word
	// '>>' word
	// '<<' word
	err_exit("Invalid token for <redirection>");
}

static t_node	*num(t_token **rest, t_token *tok)
{
	t_node	*node;

	if (tok->kind == TK_NUM)
	{
		node = new_node_num(tok->val, tok);
		node->str = tok->str;
		*rest = tok->next;
		return (node);
	}
	err_exit("Invalid token for <num>");
}

static t_node	*word(t_token **rest, t_token *tok)
{
	t_node	*node;

	if (tok->kind == TK_STRING)
	{
		node = new_node(ND_WORD, tok);
		node->str = tok->str;
		*rest = tok->next;
		return (node);
	}
	err_exit("Invalid token for <word>");
}
