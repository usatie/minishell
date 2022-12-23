/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:21:26 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 00:37:27 by susami           ###   ########.fr       */
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
		else if (tok->kind == TK_STRING)
		{
			cmd->nargs++;
			cmd->args = add_node_back(cmd->args, word(&tok, tok));
		}
		else if (tok->kind == TK_NUM)
		{
			cmd->nargs++;
			cmd->args = add_node_back(cmd->args, num(&tok, tok));
		}
		else
			syntax_error("Invalid token for <command_element>", &tok, tok);
	}
	*rest = tok;
	return (cmd);
}

static bool	is_redirection(const t_token *tok)
{
	if (equal(tok, ">"))
		return (true);
	else if (tok->kind == TK_NUM && equal(tok->next, ">"))
		return (true);
	else if (equal(tok, "<"))
		return (true);
	else if (tok->kind == TK_NUM && equal(tok->next, "<"))
		return (true);
	else if (equal(tok, ">>"))
		return (true);
	else if (tok->kind == TK_NUM && equal(tok->next, ">>"))
		return (true);
	else if (equal(tok, "<<"))
		return (true);
	return (false);
}
