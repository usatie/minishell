/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:21:26 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:23:46 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection(const t_token *tok);

// simple_command = (redirection | word)*
t_node	*simple_command(t_token **rest, t_token *tok)
{
	t_node	*cmd;

	cmd = new_node(ND_CMD, tok);
	while (!at_eof(tok) && !equal(tok, "|"))
	{
		if (is_redirection(tok))
			cmd->redirects = add_node_back(cmd->redirects, redirection(&tok,
						tok));
		// word
		else if (tok->kind == TK_STRING)
		{
			cmd->nargs++;
			cmd->args = add_node_back(cmd->args, word(&tok, tok));
		}
		// num
		else if (tok->kind == TK_NUM)
		{
			cmd->nargs++;
			cmd->args = add_node_back(cmd->args, num(&tok, tok));
		}
		// syntax error
		else
			syntax_error("Invalid token for <command_element>", &tok, tok);
	}
	*rest = tok;
	return (cmd);
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
	// '>>' word
	else if (equal(tok, ">>"))
		return (true);
	// num '>>' word
	else if (tok->kind == TK_NUM && equal(tok->next, ">>"))
		return (true);
	// '<<' word
	else if (equal(tok, "<<"))
		return (true);
	// num '<<' word
	// ^ This is invalid
	return (false);
}
