/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:06:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:23:25 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*heredoc(t_token **rest, t_token *tok);
static t_node	*redirection_output(t_token **rest, t_token *tok);
static t_node	*redirection_input(t_token **rest, t_token *tok);
static t_node	*redirection_append(t_token **rest, t_token *tok);

t_node	*redirection(t_token **rest, t_token *tok)
{
	// '<<' word
	if (equal(tok, "<<"))
		return (heredoc(rest, tok));
	// num? '>' word
	if (equal(tok, ">") || equal(tok->next, ">"))
		return (redirection_output(rest, tok));
	// num? '<' word
	if (equal(tok, "<") || equal(tok->next, "<"))
		return (redirection_input(rest, tok));
	// num? '>>' word
	if (equal(tok, ">>") || equal(tok->next, ">>"))
		return (redirection_append(rest, tok));
	// syntax error
	syntax_error("Invalid token for <redirection>", rest, tok);
	return (NULL);
}

// redirection = num? '>' word
//             | num? '<' word
//             | num? '<<' word
//             | '>>' word
static t_node	*heredoc(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node_num(STDIN_FILENO, tok);
	node = new_node_binary(ND_REDIR_HEREDOC, node, word(rest, tok->next),
			tok);
	return (node);
}

static t_node	*redirection_output(t_token **rest, t_token *tok)
{
	t_node	*node;

	// num?
	node = NULL;
	if (tok->kind == TK_NUM)
		node = num(&tok, tok);
	if (node == NULL)
		node = new_node_num(STDOUT_FILENO, tok);
	node = new_node_binary(ND_REDIR_OUT, node, word(rest, tok->next), tok);
	return (node);
}

static t_node	*redirection_input(t_token **rest, t_token *tok)
{
	t_node	*node;

	// num?
	node = NULL;
	if (tok->kind == TK_NUM)
		node = num(&tok, tok);
	if (node == NULL)
		node = new_node_num(STDIN_FILENO, tok);
	node = new_node_binary(ND_REDIR_IN, node, word(rest, tok->next), tok);
	return (node);
}

static t_node	*redirection_append(t_token **rest, t_token *tok)
{
	t_node	*node;

	// num?
	node = NULL;
	if (tok->kind == TK_NUM)
		node = num(&tok, tok);
	if (node == NULL)
		node = new_node_num(STDOUT_FILENO, tok);
	node = new_node_binary(ND_REDIR_APPEND, node, word(rest, tok->next),
			tok);
	return (node);
}
