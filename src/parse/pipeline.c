/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:12:27 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:22:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipeline = command ('|' pipeline)*
t_node	*pipeline(t_token **rest, t_token *tok)
{
	t_token	*start;
	t_node	*node;

	node = simple_command(&tok, tok);
	if (equal(tok, "|"))
	{
		start = tok;
		node = new_node_binary(ND_PIPE, node, pipeline(&tok, tok->next), start);
	}
	*rest = tok;
	return (node);
}
