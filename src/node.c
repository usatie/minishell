/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 06:49:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 16:40:11 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
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

t_node	*add_node_back(t_node *head, t_node *new_node)
{
	t_node	*cur;

	if (!head)
		return (new_node);
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
	return (head);
}

bool	equal(t_token *tok, char *op)
{
	return (memcmp(tok->pos, op, tok->len) == 0 && op[tok->len] == '\0');
}

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}
