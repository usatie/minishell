/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/18 13:30:13 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

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

static bool	is_redirection(const t_token *tok)
{
	// '>' word
	if (equal(tok, ">"))
		return (true);
	// num '>' word
	else if (tok->kind == TK_NUM && equal(tok->next, ">"))
		return (true);
	// '<' word
	else if (equal(tok, "<"))
		return (true);
	// num '<' word
	else if (tok->kind == TK_NUM && equal(tok->next, "<"))
		return (true);
	return (false);
}

// command = (redirection | word)*
static t_node	*command(t_token **rest, t_token *tok)
{
	t_node	*cmd;

	cmd = new_node(ND_CMD, tok);
	while (!at_eof(tok) && !equal(tok, "|"))
	{
		// '>' word | num '>' word
		if (is_redirection(tok))
		{
			cmd->redirects = add_node_back(cmd->redirects, redirection(&tok, tok));
			continue ;
		}
		// word
		else if (tok->kind == TK_STRING)
		{
			cmd->nargs++;
			cmd->args = add_node_back(cmd->args, word(&tok, tok));
			continue ;
		}
		// num
		else if (tok->kind == TK_NUM)
		{
			cmd->nargs++;
			cmd->args = add_node_back(cmd->args, num(&tok, tok));
			continue ;
		}
		err_exit("Invalid token for <command_element>");
	}
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
	if (equal(tok, "<"))
	{
		if (node == NULL)
			node = new_node_num(STDIN_FILENO, tok);
		node = new_node_binary(ND_REDIR_IN, node, word(rest, tok->next), tok);
		return (node);
	}
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
