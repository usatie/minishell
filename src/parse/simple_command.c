/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:21:26 by susami            #+#    #+#             */
/*   Updated: 2022/12/29 15:53:32 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool			is_control_op(t_token *tok);
static bool		is_redirection(const t_token *tok);
static t_node	*simple_command_element(t_token **rest, t_token *tok);
static void		append_element(t_node *cmd, t_node *elem);

// simple_command is terminated by control operator
// simple_command         = simple_command_element
//                        | simple_command_element simple_command
t_node	*simple_command(t_token **rest, t_token *tok)
{
	t_node	*cmd;

	cmd = new_node(ND_CMD, tok);
	append_element(cmd, simple_command_element(&tok, tok));
	while (!at_eof(tok) && !is_control_op(tok))
		append_element(cmd, simple_command_element(&tok, tok));
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

// simple_command_element = redirection
//                        | word
static t_node	*simple_command_element(t_token **rest, t_token *tok)
{
	// redirection
	if (is_redirection(tok))
		return (redirection(rest, tok));
	// word
	else if (tok->kind == TK_STRING)
		return (word(rest, tok));
	// num
	else if (tok->kind == TK_NUM)
		return (num(rest, tok));
	// syntax error
	else
	{
		syntax_error("Invalid token for <command_element>", rest, tok);
		return (NULL);
	}
}

bool	is_control_op(t_token *tok)
{
	//return (tok->kind == TK_OP && is_control_operator(tok->pos));
	return (is_control_operator(tok->pos));
}

static void	append_element(t_node *cmd, t_node *elem)
{
	if (elem == NULL)
		return ;
	if (elem->kind == ND_WORD || elem->kind == ND_NUM)
	{
		cmd->nargs++;
		cmd->args = add_node_back(cmd->args, elem);
	}
	else if (elem->kind == ND_REDIR_IN || elem->kind == ND_REDIR_OUT
			|| elem->kind == ND_REDIR_APPEND || elem->kind == ND_REDIR_HEREDOC)
	{
		cmd->redirects = add_node_back(cmd->redirects, elem);
	}
}
